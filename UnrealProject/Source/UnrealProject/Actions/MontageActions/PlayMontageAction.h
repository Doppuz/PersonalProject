// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Action.h"
#include "PlayMontageAction.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UPlayMontageAction : public UAction
{
	GENERATED_BODY()

public:

	virtual void StartAction_Implementation(AActor* Instigator) override;

	virtual void StopAction_Implementation(AActor* Instigator) override;

protected:

	UFUNCTION()
	virtual void OnPlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot|Montage")
	UAnimMontage* MontageToPlay;

	UPROPERTY()
	UAnimInstance* AI = nullptr;

};
