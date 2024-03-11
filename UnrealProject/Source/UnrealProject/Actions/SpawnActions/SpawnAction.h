// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Action.h"
#include "SpawnAction.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API USpawnAction : public UAction
{
	GENERATED_BODY()
	
public:

	virtual void StartAction_Implementation(AActor* Instigator) override;

};
