// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enums_Movement.generated.h"

UENUM(BlueprintType)
enum class EMovementState
{
	WALKING,
	SPRINTING,
	MAX UMETA(Hidden)
};

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UEnums_Movement : public UObject
{
	GENERATED_BODY()
	
};
