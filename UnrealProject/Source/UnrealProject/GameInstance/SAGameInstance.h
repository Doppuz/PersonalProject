// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "SAGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API USAGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	FStreamableManager StreamableManager;
};
