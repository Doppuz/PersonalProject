// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "../Interfaces/AsyncLoadInterface.h"
#include "GameplayTagContainer.h"
#include "GameSubsystemSettings.generated.h"

UCLASS(Config = Game, defaultconfig)
class UNREALPROJECT_API UGameSubsystemSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "GameSubsystemSetting")
	FPrimaryAssetId PA_GameSubsystemSetting;

};
