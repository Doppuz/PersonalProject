// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Action.h"
#include "../../Enums/Enums_Stat.h"
#include "StatAction.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UStatAction : public UAction
{
	GENERATED_BODY()
	
public:

	UStatAction();

	virtual void StartAction_Implementation(AActor* Instigator) override;

	virtual void StopAction_Implementation(AActor* Instigator) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintreadOnly, Category = "Stat")
	TArray<FStatCategoryValue> ValuesToChange;

};
