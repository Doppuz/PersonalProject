// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsManager.h"
#include "../../Library/QuickAccessLibrary.h"
#include "../../GameInstance/SAGameInstance.h"
#include "../../Stats/Stat.h"
#include "../../Library/QuickAccessLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "../../Subsystem/WorldSubsystem/WorldSubsystem_GlobalEvents.h"

static int DebugPrintStats = 0;
FAutoConsoleVariableRef CVarDebugPrintStats(TEXT("DebugPrintStats"), DebugPrintStats, TEXT("Print stats info for each stats components"), ECVF_Cheat);

UStatsManager::UStatsManager()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
}

// Called when the game starts
void UStatsManager::BeginPlay()
{
	Super::BeginPlay();

	GI = UQuickAccessLibrary::GetGameInstance(GetOwner());
	WS_GlobalEvents = GetOuter()->GetWorld()->GetSubsystem<UWorldSubsystem_GlobalEvents>();

	if (GetOwner() && GetOwner()->HasAuthority())
	{
		for (int i = 0; i < DefaultStats.Num(); i++)
		{
			AddStat(DefaultStats[i]);
		}
	}
}

void UStatsManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (DebugPrintStats > 0 && GEngine)
	{
		FString AutorityMsg = GetOwner()->HasAuthority() ? "Server" : "Client";
		FColor ServerClientColor = GetOwner()->HasAuthority() ? FColor::Purple : FColor::Orange;
		FString DebugMsg = AutorityMsg + " -> " + GetNameSafe(GetOwner()) + " : ";
		GEngine->AddOnScreenDebugMessage(-1, DeltaTime, ServerClientColor, DebugMsg);

		// Draw All Actions
		for (UStat* Stat : CurrentStats)
		{
			FStatValue CurrentStatValue = Stat->GetStatValue();
			FString ActionMsg = FString::Printf(TEXT("[%s] %s Stat: Min %f, Max %f, Current %f"), *GetNameSafe(GetOwner()), *GetNameSafe(Stat),
				CurrentStatValue.MinValue, CurrentStatValue.MaxValue, CurrentStatValue.CurrentValue);

			GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::White, ActionMsg);
		}
	}

}

void UStatsManager::AddStat(TSoftClassPtr<UStat> StatSoftClass)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		if (ensureAlways(GI))
		{
			GI->StreamableManager.RequestAsyncLoad(StatSoftClass.ToSoftObjectPath(), [this, StatSoftClass]()
				{
					TSubclassOf<UStat> StatClass = StatSoftClass.Get();

					if (StatClass)
					{
						UStat* NewStat = NewObject<UStat>(this, StatClass);

						if (NewStat)
						{
							CurrentStats.Add(NewStat);

							NewStat->Initialize();
						}
					}
				});
		}
	}
}

void UStatsManager::ChangeStat(AActor* Instigator, EStatCategory TargetStat, float Amount)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		for (int i = 0; i < CurrentStats.Num(); i++)
		{
			if (CurrentStats[i]->GetStatCategory() == TargetStat)
			{
				FStat_Broadcast Stat_Broadcast = CurrentStats[i]->ChangeStat(Instigator, Amount);

				Multicast_ChangeStat(Stat_Broadcast);
			}
		}
	}
}

#pragma region RPC

void UStatsManager::Multicast_ChangeStat_Implementation(FStat_Broadcast StatBroadcast)
{
	if (ensure(WS_GlobalEvents))
	{
		WS_GlobalEvents->OnStatChanged.Broadcast(StatBroadcast);
	}
}

#pragma endregion

#pragma region Replication

void UStatsManager::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UStatsManager, CurrentStats);
}

bool UStatsManager::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
	for (UStat* Stat : CurrentStats)
	{
		if (Stat)
		{
			WroteSomething |= Channel->ReplicateSubobject(Stat, *Bunch, *RepFlags);
		}
	}

	return WroteSomething;
}

#pragma endregion