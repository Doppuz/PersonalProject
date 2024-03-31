// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnActionBase.h"
#include "SingleSpawnAction.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API USingleSpawnAction : public USpawnActionBase
{
	GENERATED_BODY()

public:

	virtual void StartAction_Implementation(AActor* Instigator) override;

	virtual void StopAction_Implementation(AActor* Instigator) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn", meta = (DisplayName = "ClassToSpawn"))
	TArray<TSoftClassPtr<AActor>> SoftClassesToSpawn;

};
