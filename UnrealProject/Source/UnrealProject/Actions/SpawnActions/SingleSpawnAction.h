// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Action.h"
#include "SingleSpawnAction.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API USingleSpawnAction : public UAction
{
	GENERATED_BODY()

public:

	virtual void StartAction_Implementation(AActor* Instigator) override;

	virtual void StopAction_Implementation(AActor* Instigator) override;

protected:

	virtual void SpawnActor(TSubclassOf<AActor> ClassToSpawn);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn", meta = (DisplayName = "ClassToSpawn"))
	TArray<TSoftClassPtr<AActor>> SoftClassesToSpawn;

};
