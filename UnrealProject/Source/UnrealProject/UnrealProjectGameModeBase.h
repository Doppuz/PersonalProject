// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnrealProjectGameModeBase.generated.h"

class UWorldSubsystem_GlobalEvents;

UCLASS()
class UNREALPROJECT_API AUnrealProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	UFUNCTION()
	FORCEINLINE bool GetAreAllPlayersReady() const { return AreAllPlayersReady; };

protected:

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	UFUNCTION()
	void OnGameModePostLoginEvent(AGameModeBase* GameMode, APlayerController* PlayerController);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Players")
	int RequiredNumberOfPlayers = 2;

	UPROPERTY()
	TObjectPtr<UWorldSubsystem_GlobalEvents> WS_GlobalEvents;

	UPROPERTY()
	bool AreAllPlayersReady = false;

};
