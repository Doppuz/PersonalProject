// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PDA_GameSubsystem.generated.h"

class ASpawner;

UCLASS()
class UNREALPROJECT_API UPDA_GameSubsystem : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn management")
	TArray<TSoftObjectPtr<ASpawner>> RangeSpawners;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn management")
	TSoftObjectPtr<UCurveFloat> RangeSpawnerCurve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn management")
	TArray<TSoftObjectPtr<ASpawner>> MeleeSpawners;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn management")
	TSoftObjectPtr<UCurveFloat> MeleeSpawnerCurve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn management")
	TArray<TSoftObjectPtr<ASpawner>> PowerupSpawners;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn management")
	TSoftObjectPtr<UCurveFloat> PowerupSpawnerCurve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn management")
	TSoftObjectPtr<ASpawner> CoinSpawner;

public:

	FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("GameSubsystem", GetFName());
	}
};
