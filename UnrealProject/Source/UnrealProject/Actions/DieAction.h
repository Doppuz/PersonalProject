// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "DieAction.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UDieAction : public UAction
{
	GENERATED_BODY()
	
public:

	UDieAction();

protected:

	virtual void StartAction_Implementation(AActor* Instigator) override;

	void OnEndTimer();

	UPROPERTY(EditAnywhere, Category = "Dead timer")
	float DeadTimerDuration = 2.f;

	FTimerHandle DeadTimerHandle;

};
