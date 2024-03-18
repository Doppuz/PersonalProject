// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Action.h"
#include "AddWidgetAction.generated.h"

class UGeneralUserWidget;

UCLASS()
class UNREALPROJECT_API UAddWidgetAction : public UAction
{
	GENERATED_BODY()
	
public:

	virtual void StartAction_Implementation(AActor* Instigator) override;

	virtual void StopAction_Implementation(AActor* Instigator) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget")
	TSubclassOf<UGeneralUserWidget> WidgetToAdd;

};
