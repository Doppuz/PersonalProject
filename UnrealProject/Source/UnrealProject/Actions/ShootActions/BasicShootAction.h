// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MontageActions/PlayMontageAction.h"
#include "BasicShootAction.generated.h"

class ABasicProjectile;

UCLASS(Blueprintable)
class UNREALPROJECT_API UBasicShootAction : public UPlayMontageAction
{
	GENERATED_BODY()
	
protected:

	virtual void OnPlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload) override;

	virtual void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	FName ShootSocket = "ShootSocket";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	TSubclassOf<ABasicProjectile> BasicProjectileClass;

};
