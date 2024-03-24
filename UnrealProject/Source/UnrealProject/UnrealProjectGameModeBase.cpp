// Copyright Epic Games, Inc. All Rights Reserved.


#include "UnrealProjectGameModeBase.h"
#include "Subsystem/WorldSubsystem/WorldSubsystem_GlobalEvents.h"

void AUnrealProjectGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	WS_GlobalEvents = GetWorld()->GetSubsystem<UWorldSubsystem_GlobalEvents>();

#if WITH_EDITOR

	const ULevelEditorPlaySettings* PlayInSettings = GetDefault<ULevelEditorPlaySettings>();

	if (ensureAlways(PlayInSettings))
	{
		PlayInSettings->GetPlayNumberOfClients(RequiredNumberOfPlayers);
	}

#endif
}

void AUnrealProjectGameModeBase::GenericPlayerInitialization(AController* NewPlayer)
{
	Super::GenericPlayerInitialization(NewPlayer);

	PlayerInitialized += 1;

	if (PlayerInitialized >= RequiredNumberOfPlayers && ensureAlways(WS_GlobalEvents))
	{
		AreAllPlayersReady = true;
		WS_GlobalEvents->OnAllPlayersReady.Broadcast(this);
	}
}
