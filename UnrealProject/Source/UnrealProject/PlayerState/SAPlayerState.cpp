// Fill out your copyright notice in the Description page of Project Settings.


#include "SAPlayerState.h"
#include "../Subsystem/WorldSubsystem/WorldSubsystem_GlobalEvents.h"

void ASAPlayerState::BeginPlay()
{
	Super::BeginPlay();

	WS_GlobalEvents = GetWorld()->GetSubsystem<UWorldSubsystem_GlobalEvents>();
}

void ASAPlayerState::UpdatePlayerScore(float AmountToAdd)
{
	if (ensureAlways(HasAuthority()))
	{
		float OldValue = GetScore();
		SetScore(OldValue + AmountToAdd);

		Multicast_UpdatePlayerScore(OldValue, GetScore());
	}
}

void ASAPlayerState::Multicast_UpdatePlayerScore_Implementation(float OldValue, float NewValue)
{
	if (ensureAlways(WS_GlobalEvents))
	{
		WS_GlobalEvents->OnScoreUpdated.Broadcast(OldValue, NewValue);
	}
}
