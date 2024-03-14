// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"
#include "GameSubsystemSettings.generated.h"

class ASpawner;

UCLASS(Config = Game)
class UNREALPROJECT_API UGameSubsystemSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn management")
	TArray<TSoftObjectPtr<ASpawner>> RangeSpawners;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn management")
	FGameplayTag SpawnActionName;
};
