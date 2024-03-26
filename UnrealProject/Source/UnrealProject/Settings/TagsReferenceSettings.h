// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"
#include "TagsReferenceSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game)
class UNREALPROJECT_API UTagsReferenceSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:

	UPROPERTY(config, EditDefaultsOnly, BlueprintReadOnly, Category = "Shield")
	FGameplayTag ShieldTag;
};
