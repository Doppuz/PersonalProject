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

	virtual void StartAction_Implementation(AActor* Instigator) override;

	virtual void StopAction_Implementation(AActor* Instigator) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot|Montage")
	UAnimMontage* DieMontage;

protected:

	UPROPERTY()
	UAnimInstance* AI = nullptr;

};
