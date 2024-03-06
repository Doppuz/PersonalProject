// Fill out your copyright notice in the Description page of Project Settings.


#include "Stat.h"
#include "../Subsystem/WorldSubsystem/WorldSubsystem_GlobalEvents.h"
#include "../Components/GeneralComponents/StatsManager.h"

void UStat::Initialize()
{
	if (ensureAlways(GetOuter()) && ensureAlways(GetOuter()->GetWorld()))
	{
		StatsManagerRef = Cast<UStatsManager>(GetOuter());
		WS_GlobalEvents = GetOuter()->GetWorld()->GetSubsystem<UWorldSubsystem_GlobalEvents>();
	}
}

void UStat::ChangeStat(AActor* Instigator, float Value)
{
	if (ensure(StatsManagerRef) && ensure(StatsManagerRef->GetOwner()) && StatsManagerRef->GetOwner()->HasAuthority())
	{
		float OldValue = StatValue.CurrentValue;
		StatValue.CurrentValue = FMath::Clamp(StatValue.CurrentValue + Value, StatValue.MinValue, StatValue.MaxValue);

		Multicast_ChangeStat(StatsManagerRef->GetOwner(), OldValue, StatValue.CurrentValue);

		if (StatValue.CurrentValue == StatValue.MinValue)
		{
			OnStatReachesMinValue(Instigator);
		}
	}
}

void UStat::OnStatReachesMinValue_Implementation(AActor* Instigator)
{
	//override on children
}

void UStat::Multicast_ChangeStat_Implementation(AActor* Owner, float OldValue, float NewValue)
{
	if (ensure(WS_GlobalEvents))
	{
		WS_GlobalEvents->OnStatChanged.Broadcast(Owner, OldValue, NewValue);
	}
}

#pragma region Replication

void UStat::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UStat, StatValue);
}

#pragma endregion
