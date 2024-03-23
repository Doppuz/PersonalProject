// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameplayTagContainer.h"
#include "WorldSubsystem_GameManager.generated.h"

class ASpawner;
class UGameSubsystemSettings;
class UWorldSubsystem_GlobalEvents;
class AUnrealProjectGameModeBase;

UCLASS()
class UNREALPROJECT_API UWorldSubsystem_GameManager : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	
public:

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Tick(float DeltaTime) override;

	virtual TStatId GetStatId() const override;

	void UpdateManager();

	void UpdatePowerUpManager();

#pragma region Events

	UFUNCTION()
	void OnAllPlayersReady(AGameModeBase* CurrentGameMode);

#pragma endregion

#pragma region Debug

	void PrintSpawners(float DeltaTime);

#pragma endregion

protected:

	void ActivateSpawner(TSoftObjectPtr<ASpawner> InSpawner, FGameplayTag ActionName);

protected:

	UPROPERTY()
	const UGameSubsystemSettings* GameSubsystemSettings;

	UPROPERTY()
	TObjectPtr<UWorldSubsystem_GlobalEvents> WS_GlobalEvents;

	UPROPERTY()
	USAGameInstance* GI;

	UPROPERTY()
	bool bActivateTick = false;

#pragma region Enemies

	UPROPERTY()
	float CheckFrequency = 3.f;

	UPROPERTY()
	float CurrentTick = 0.f;

#pragma endregion

#pragma region Powerups

	UPROPERTY()
	float PowerupCheckFrequency = 8.f;

	UPROPERTY()
	float CurrentPowerUpTick = 0.f;

#pragma endregion

#pragma region Score

	UPROPERTY()
	float TotalScore = 0.f;

	UPROPERTY()
	float ScoreCheckFrequency = 1.f;

	UPROPERTY()
	float CurrentScoreTick = 0.f;

#pragma endregion

};
