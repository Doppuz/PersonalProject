// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"
#include "TagsReferenceSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, defaultconfig)
class UNREALPROJECT_API UTagsReferenceSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags")
	FGameplayTag ShieldTag;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags")
	FGameplayTag DieTag;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags")
	FGameplayTag SpawnActionName;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags")
	FGameplayTag HitReactionActionName;
};
