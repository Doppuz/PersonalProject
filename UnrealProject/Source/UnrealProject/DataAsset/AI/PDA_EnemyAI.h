// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PDA_EnemyAI.generated.h"

class ABaseEnemy;

UCLASS()
class UNREALPROJECT_API UPDA_EnemyAI : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn Info")
	int32 MinLevelToSpawn = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn Info")
	int32 MaxLevelToSpawn = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn Info", meta = (DisplayName = "BaseEnemyClass"))
	TSoftClassPtr<ABaseEnemy> BaseEnemySoftClass;

	FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("Enemy", GetFName());
	}

};
