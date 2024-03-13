// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameplayTagContainer.h"
#include "WorldSubsystem_GameManager.generated.h"

class ASpawner;

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

protected:

	void ActivateSpawner(TSoftObjectPtr<ASpawner> InSpawner, FGameplayTag ActionName);

	UFUNCTION()
	void OnAssetLoaded(FPrimaryAssetId LoadedId);

protected:

	UPROPERTY()
	FPrimaryAssetId PDA_ID_WS_GameManager;

	UPROPERTY()
	float CheckFrequency = 5.f;

	UPROPERTY()
	float CurrentTick = 0.f;
};
