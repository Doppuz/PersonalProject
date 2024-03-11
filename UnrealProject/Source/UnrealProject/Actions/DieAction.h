// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Actions/MontageActions/PlayMontageAction.h"
#include "DieAction.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UDieAction : public UPlayMontageAction
{
	GENERATED_BODY()
	
public:

	UDieAction();

protected:

	virtual void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted) override;

};
