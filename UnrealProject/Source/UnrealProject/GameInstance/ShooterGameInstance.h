// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "ShooterGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	FStreamableManager StreamableManager;
};
