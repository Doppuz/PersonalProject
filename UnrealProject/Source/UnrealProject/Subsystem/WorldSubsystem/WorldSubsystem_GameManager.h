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
class UTagsReferenceSettings;

UCLASS()
class UNREALPROJECT_API UWorldSubsystem_GameManager : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	
public:

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Tick(float DeltaTime) override;

	virtual TStatId GetStatId() const override;

	void UpdateRangeEnemiesManager();

	void UpdatePowerUpManager();

	void UpdateMeleeEnemiesManager();

	void UpdateCoinsManager();

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
	const UTagsReferenceSettings* TagsReferenceSettings;

	UPROPERTY()
	TObjectPtr<UWorldSubsystem_GlobalEvents> WS_GlobalEvents;

	UPROPERTY()
	class USAGameInstance* GI;

	UPROPERTY()
	bool bActivateTick = false;

	UPROPERTY()
	float TotalGameDuration = 0.f;

#pragma region MeleeEnemies

	UPROPERTY()
	float CheckMeleeEnemiesFrequency = 6.f;

	UPROPERTY()
	float CurrentMeleeEnemiesTick = 0.f;

#pragma endregion

#pragma region RangeEnemies

	UPROPERTY()
	float CheckRangeEnemiesFrequency = 7.f;

	UPROPERTY()
	float CurrentRangeEnemiesTick = 0.f;

#pragma endregion

#pragma region Powerups

	UPROPERTY()
	float PowerupCheckFrequency = 10.f;

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

#pragma region Coins

	UPROPERTY()
	float CoinsCheckFrequency = 4.f;

	UPROPERTY()
	float CurrentCoinsTick = 0.f;

#pragma endregion

};
