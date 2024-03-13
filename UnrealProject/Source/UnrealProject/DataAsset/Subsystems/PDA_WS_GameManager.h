// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PDA_WS_GameManager.generated.h"

class ASpawner;

UCLASS()
class UNREALPROJECT_API UPDA_WS_GameManager : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Asset")
	TArray<TSoftObjectPtr<ASpawner>> RangeSpawners;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Asset")
	FGameplayTag SpawnActionName;

	FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("Subsystem", GetFName());
	}
};
