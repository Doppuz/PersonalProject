// Copyright Epic Games, Inc. All Rights Reserved.


#include "UnrealProjectGameModeBase.h"
#include "Subsystem/WorldSubsystem/WorldSubsystem_GlobalEvents.h"

void AUnrealProjectGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	WS_GlobalEvents = GetWorld()->GetSubsystem<UWorldSubsystem_GlobalEvents>();

	FGameModeEvents::GameModePostLoginEvent.AddUObject(this, &AUnrealProjectGameModeBase::OnGameModePostLoginEvent);
}

void AUnrealProjectGameModeBase::OnGameModePostLoginEvent(AGameModeBase* GameMode, APlayerController* NewPlayer)
{
	if (GetNumPlayers() == RequiredNumberOfPlayers && ensureAlways(WS_GlobalEvents))
	{
		AreAllPlayersReady = true;
		WS_GlobalEvents->OnAllPlayersReady.Broadcast(this);
	}
}
