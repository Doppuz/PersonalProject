// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Action.h"
#include "BasicShootAction.generated.h"

class ABasicProjectile;

UCLASS(Blueprintable)
class UNREALPROJECT_API UBasicShootAction : public UAction
{
	GENERATED_BODY()
	
public:

	virtual void StartAction_Implementation(AActor* Instigator) override;

	virtual void StopAction_Implementation(AActor* Instigator) override;

protected:

	UFUNCTION()
	void OnPlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	FName ShootSocket = "ShootSocket";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot", meta = (DisplayName = "BasicProjectileClass"))
	TSoftClassPtr<ABasicProjectile> BasicProjectileSoftClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot|Montage")
	UAnimMontage* ShootMontage;

	UPROPERTY()
	UAnimInstance* AI = nullptr;
};
