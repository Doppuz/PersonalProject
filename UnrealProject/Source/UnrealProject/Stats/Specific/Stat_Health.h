// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Stat.h"
#include "Stat_Health.generated.h"

class UAction;

UCLASS()
class UNREALPROJECT_API UStat_Health : public UStat
{
	GENERATED_BODY()
	
public:

	virtual FStat_Broadcast ChangeStat(AActor* Instigator, float Value) override;

protected:

	virtual void OnStatReachesMinValue_Implementation(AActor* Instigator) override;

};
