// Fill out your copyright notice in the Description page of Project Settings.


#include "Stat.h"
#include "../Components/GeneralComponents/StatsManager.h"
#include "Net/UnrealNetwork.h"

void UStat::Initialize()
{
	if (ensureAlways(GetOuter()) && ensureAlways(GetOuter()->GetWorld()))
	{
		StatsManagerRef = Cast<UStatsManager>(GetOuter());
	}
}

FStat_Broadcast UStat::ChangeStat(AActor* Instigator, float Value)
{
	if (ensure(StatsManagerRef) && ensure(StatsManagerRef->GetOwner()) && StatsManagerRef->GetOwner()->HasAuthority())
	{
		float OldValue = StatValue.CurrentValue;
		StatValue.CurrentValue = FMath::Clamp(StatValue.CurrentValue + Value, StatValue.MinValue, StatValue.MaxValue);

		if (OldValue != StatValue.MinValue && StatValue.CurrentValue == StatValue.MinValue)
		{
			OnStatReachesMinValue(Instigator);
		}

		return FStat_Broadcast(StatsManagerRef->GetOwner(), StatValue, OldValue, StatCategory);
	}

	return FStat_Broadcast();
}

void UStat::OnStatReachesMinValue_Implementation(AActor* Instigator)
{
	//override on children
}

#pragma region Replication

void UStat::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UStat, StatValue);
}

#pragma endregion
