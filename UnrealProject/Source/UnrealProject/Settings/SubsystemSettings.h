// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "SubsystemSettings.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API USubsystemSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data Asset")
	FPrimaryAssetId PDA_ID_WS_GameManager;
};
