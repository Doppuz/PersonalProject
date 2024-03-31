// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"
#include "GameSubsystemSettings.generated.h"

class ASpawner;

UCLASS(Config = Game, defaultconfig)
class UNREALPROJECT_API UGameSubsystemSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Spawn management")
	TArray<TSoftObjectPtr<ASpawner>> RangeSpawners;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Spawn management")
	TSoftObjectPtr<UCurveFloat> RangeSpawnerCurve;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Spawn management")
	TArray<TSoftObjectPtr<ASpawner>> MeleeSpawners;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Spawn management")
	TSoftObjectPtr<UCurveFloat> MeleeSpawnerCurve;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Spawn management")
	TArray<TSoftObjectPtr<ASpawner>> PowerupSpawners;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Spawn management")
	TSoftObjectPtr<UCurveFloat> PowerupSpawnerCurve;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Spawn management")
	TSoftObjectPtr<ASpawner> CoinSpawner;
};
