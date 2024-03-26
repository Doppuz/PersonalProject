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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shield")
	float ShieldAmount = 20;;

	UPROPERTY()
	UStaticMeshComponent* ShieldComponent;

	UPROPERTY()
	UCapsuleComponent* CapsuleComponent;

};
