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

	UFUNCTION()
	virtual void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	UAnimMontage* MontageToPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	float InitialMontageSpeed = 1.f;

	UPROPERTY()
	UAnimInstance* AI = nullptr;

};
