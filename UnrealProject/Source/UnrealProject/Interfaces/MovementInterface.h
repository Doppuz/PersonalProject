// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../Enums/Enums_Movement.h"
#include "MovementInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMovementInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREALPROJECT_API IMovementInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION()
	virtual FVector GetCurrentMovementSpeed() = 0;

	UFUNCTION()
	virtual void SetCurrentMovementSpeed(float InValue) = 0;

	UFUNCTION()
	virtual class UMovementManager* GetMovementManager() = 0;

	UFUNCTION()
	virtual void SetCurrentMovementState(EMovementState InState);

};
