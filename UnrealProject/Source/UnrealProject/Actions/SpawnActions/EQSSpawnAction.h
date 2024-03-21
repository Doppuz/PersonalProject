// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SingleSpawnAction.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EQSSpawnAction.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UEQSSpawnAction : public USingleSpawnAction
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn|EQS")
	class UEnvQuery* SpawnQuery;

protected:

	void OnSpawnQueryFinished(TSharedPtr<FEnvQueryResult> Result);

	virtual void SpawnActor(TSubclassOf<AActor> ClassToSpawn) override;

private:

	UPROPERTY()
	TSubclassOf<AActor> ClassToSpawn;

};
