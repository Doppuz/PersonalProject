// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Action.h"
#include "DashAction.generated.h"

class UNiagaraSystem;

UCLASS()
class UNREALPROJECT_API UDashAction : public UAction
{
	GENERATED_BODY()

protected:

	virtual void StartAction_Implementation(AActor* Instigator) override;

	virtual void StopAction_Implementation(AActor* Instigator) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dash")
	float DashDuration = 500;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dash")
	float DashDistance = 4000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dash")
	FVector DashEffectScale = FVector(1.f, 1.f, 1.f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dash")
	FName DashEffectSocketName = "DashEffectSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dash")
	float DashEffectSpeed = 1.f;
	
	UPROPERTY(EditAnywhere, Category = "Dash")
	TObjectPtr<UNiagaraSystem> DashEffect;

	UPROPERTY()
	FTimerHandle DashTimerHandle;

};
