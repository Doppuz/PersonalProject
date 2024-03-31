// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Action.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "SpawnActionBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API USpawnActionBase : public UAction
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn|EQS")
	bool bUseEQS = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn|EQS", meta = (EditCondition = "bUseEQS", EditConditionHides))
	class UEnvQuery* SpawnQuery;

protected:

	virtual void OnSpawnQueryFinished(TSharedPtr<FEnvQueryResult> Result);

	void SpawnActorWithEQS(TSubclassOf<AActor> InClassToSpawn);

	void SpawnActor(TSubclassOf<AActor> InClassToSpawn);

private:

	UPROPERTY()
	TSubclassOf<AActor> ClassToSpawn;

};
