// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Stat.h"
#include "Stat_Shield.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UStat_Shield : public UStat
{
	GENERATED_BODY()
	
protected:

	virtual void OnStatReachesMinValue_Implementation(AActor* Instigator) override;

};
