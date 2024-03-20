// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Action.h"
#include "ShieldAction.generated.h"

class UStaticMeshComponent;
class UCapsuleComponent;

UCLASS()
class UNREALPROJECT_API UShieldAction : public UAction
{
	GENERATED_BODY()

public:

	virtual void Initialize(UActionComponent* NewActionComp) override;

	virtual void StartAction_Implementation(AActor* Instigator) override;

	virtual void StopAction_Implementation(AActor* Instigator) override;

protected:

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shield")
	float ShieldHealth = 20.f;

	UPROPERTY(replicated)
	float CurrentDamage = 0.f;

	UPROPERTY()
	UStaticMeshComponent* ShieldComponent;

	UPROPERTY()
	UCapsuleComponent* CapsuleComponent;

};
