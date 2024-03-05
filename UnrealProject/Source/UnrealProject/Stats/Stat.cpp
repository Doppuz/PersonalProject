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
	float OldValue = StatValue.CurrentValue;
	StatValue.CurrentValue = FMath::Clamp(StatValue.CurrentValue + Value, StatValue.MinValue, StatValue.MaxValue);

	if (ensure(WS_GlobalEvents) && ensure(StatsManagerRef))
	{
		WS_GlobalEvents->OnStatChanged.Broadcast(StatsManagerRef->GetOwner(), OldValue, StatValue.CurrentValue);
	}

	if (StatValue.CurrentValue == StatValue.MinValue)
	{
		OnStatReachesMinValue(Instigator);
	}
}

void UStat::OnStatReachesMinValue_Implementation(AActor* Instigator)
{
	//override on children
}
