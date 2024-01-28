// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttackDefenseInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAttackDefenseInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREALPROJECT_API IAttackDefenseInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION()
	virtual float GetAttackRange() = 0;

	UFUNCTION()
	virtual float GetDefenseRange() = 0;

};
