// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionComponent.h"
#include "../../Library/QuickAccessLibrary.h"
#include "../../GameInstance/SAGameInstance.h"
#include "../../Actions/Action.h"
#include "../../Library/QuickAccessLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "../../Subsystem/WorldSubsystem/WorldSubsystem_GlobalEvents.h"

static int DebugPrintClassActions = 0;
FAutoConsoleVariableRef CVarDebugPrintClassActions(TEXT("DebugPrintClassActions"), DebugPrintClassActions, TEXT("Print actions info for the specific class set on the gameinstance"), ECVF_Cheat);

UActionComponent::UActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
}


// Called when the game starts
void UActionComponent::BeginPlay()
{
	Super::BeginPlay();

	GI = UQuickAccessLibrary::GetGameInstance(GetOwner());
	WS_GlobalEvents = GetWorld()->GetSubsystem<UWorldSubsystem_GlobalEvents>();

	if (GetOwner()->HasAuthority())
	{
		if (QL::GetAreAllPlayersReady(this))
		{
			//No need to get the gamemode
			OnAllPlayersReady(nullptr);
		}
		else if (ensureAlways(WS_GlobalEvents))
		{
			WS_GlobalEvents->OnAllPlayersReady.AddDynamic(this, &UActionComponent::OnAllPlayersReady);
		}
	}
}

void UActionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (GetOwner()->HasAuthority() && ensureAlways(WS_GlobalEvents) && WS_GlobalEvents->OnAllPlayersReady.Contains(this, "OnAllPlayersReady"))
	{
		WS_GlobalEvents->OnAllPlayersReady.RemoveDynamic(this, &UActionComponent::OnAllPlayersReady);
	}
}

void UActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (DebugPrintClassActions > 0 && GEngine && ensureAlways(GI))
	{
		if (QL::ClassIsChildOfSoft(GI->GetDebugActionComponentClass(), GetOwner()->GetClass()))
		{
			FString AutorityMsg = GetOwner()->HasAuthority() ? "Server" : "Client";
			FColor ServerClientColor = GetOwner()->HasAuthority() ? FColor::Purple : FColor::Orange;
			FString DebugMsg = AutorityMsg + " -> " + GetNameSafe(GetOwner()) + " : " + ActiveGameplayTags.ToStringSimple();
			GEngine->AddOnScreenDebugMessage(-1, DeltaTime, ServerClientColor, DebugMsg);

			// Draw All Actions
			for (UAction* Action : CurrentActions)
			{
				FColor TextColor = Action->GetIsRunning() ? FColor::Blue : FColor::White;
				FString ActionMsg = FString::Printf(TEXT("[%s] Action: %s"), *GetNameSafe(GetOwner()), *GetNameSafe(Action));

				GEngine->AddOnScreenDebugMessage(-1, DeltaTime, TextColor, ActionMsg);
			}
		}
	}
}

void UActionComponent::AddAction(AActor* Instigator, TSoftClassPtr<UAction> SoftActionClass)
{
	//Return if not the server
	if (!GetOwner()->HasAuthority())
	{
		return;
	}

	if (ensureAlways(GI))
	{
		GI->StreamableManager.RequestAsyncLoad(SoftActionClass.ToSoftObjectPath(), [this, Instigator, SoftActionClass]()
			{
				if (ContainsAction(SoftActionClass))
				{
					return;
				}

				TSubclassOf<UAction> ActionClass = SoftActionClass.Get();

				if (ActionClass)
				{
					UAction* NewAction = NewObject<UAction>(this, ActionClass);

					if (NewAction)
					{
						CurrentActions.Add(NewAction);
						
						NewAction->Initialize(this);

						if (NewAction->GetAutoPlay() && NewAction->CanStart())
						{
							NewAction->StartAction(Instigator);
						}
					}
				}
			});
	}
}

void UActionComponent::RemoveAction(AActor* Instigator, UAction* ActionToRemove)
{	
	//Return if not the server
	if (!GetOwner()->HasAuthority())
	{
		return;
	}

	for (int i = 0; i < CurrentActions.Num(); i++)
	{
		if (CurrentActions[i] == ActionToRemove)
		{
			CurrentActions.RemoveAt(i);
			return;
		}
	}
}

void UActionComponent::StartActionByName(AActor* Instigator, FGameplayTag ActionName)
{
	for (int i = 0; i < CurrentActions.Num(); i++)
	{
		if (CurrentActions[i]->GetActionName() == ActionName)
		{
			if (!CurrentActions[i]->CanStart())
			{
				if (GEngine)
				{
					//FString FailedMsg = FString::Printf(TEXT("Failed to run: %s"), *ActionName.ToString());
					//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FailedMsg);
				}
				continue;
			}

			// If I am the client
			if (!GetOwner()->HasAuthority())
			{
				ServerStartAction(Instigator, ActionName);
			}

			CurrentActions[i]->StartAction(Instigator);
		}
	}
}

void UActionComponent::StopActionByName(AActor* Instigator, FGameplayTag ActionName)
{
	for (int i = 0; i < CurrentActions.Num(); i++)
	{
		if (CurrentActions[i]->GetActionName() == ActionName)
		{
			if (!CurrentActions[i]->GetIsRunning())
			{
				if (GEngine)
				{
					FString FailedMsg = FString::Printf(TEXT("Failed to stop: %s"), *ActionName.ToString());
					GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FailedMsg);
				}
				continue;
			}

			// If I am the client
			if (!GetOwner()->HasAuthority())
			{
				ServerStopAction(Instigator, ActionName);
			}

			CurrentActions[i]->StopAction(Instigator);
		}
	}
}

UAction* UActionComponent::GetAction(TSoftClassPtr<UAction> ActionSoftClass)
{
	for (int i = 0; i < CurrentActions.Num(); i++)
	{
		if (CurrentActions[i] && QL::SoftClassIsChildOf(ActionSoftClass, CurrentActions[i]->GetClass()))
		{
			return CurrentActions[i];
		}
	}

	return nullptr;
}

bool UActionComponent::ContainsActiveGameplayTags(FGameplayTagContainer InTags)
{
	return ActiveGameplayTags.HasAny(InTags);
}

void UActionComponent::AddActiveTags(FGameplayTagContainer InTags)
{
	ActiveGameplayTags.AppendTags(InTags);
}

void UActionComponent::RemoveActiveTags(FGameplayTagContainer InTags)
{
	ActiveGameplayTags.RemoveTags(InTags);
}

#pragma region Events

void UActionComponent::OnAllPlayersReady(AGameModeBase* CurrentGameMode)
{
	if (GetOwner()->HasAuthority())
	{
		for (int i = 0; i < DefaultActions.Num(); i++)
		{
			AddAction(GetOwner(), DefaultActions[i]);
		}
	}
}

#pragma endregion

#pragma region Server

void UActionComponent::ServerStartAction_Implementation(AActor* Instigator, FGameplayTag ActionName)
{
	StartActionByName(Instigator, ActionName);
}

void UActionComponent::ServerStopAction_Implementation(AActor* Instigator, FGameplayTag ActionName)
{
	StopActionByName(Instigator, ActionName);
}

#pragma endregion

#pragma region Replication

void UActionComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UActionComponent, CurrentActions);
	DOREPLIFETIME(UActionComponent, ActiveGameplayTags);
}

bool UActionComponent::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
	for (UAction* Action : CurrentActions)
	{
		if (Action)
		{
			WroteSomething |= Channel->ReplicateSubobject(Action, *Bunch, *RepFlags);
		}
	}

	return WroteSomething;
}

bool UActionComponent::ContainsAction(TSoftClassPtr<UAction> SoftActionClass)
{
	for (int i = 0; i < CurrentActions.Num(); i++)
	{
		if (CurrentActions[i] && CurrentActions[i]->GetClass() == SoftActionClass)
		{
			return true;
		}
	}

	return false;
}

void UActionComponent::PrintSingleDebugActions()
{
	DebugPrintSingleActions = !DebugPrintSingleActions;
}

#pragma endregion
