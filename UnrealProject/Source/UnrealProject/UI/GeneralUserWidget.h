// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GeneralUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UGeneralUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetWidgetOwner(AActor* InWidgetOwner);

	UFUNCTION()
	FORCEINLINE AActor* GetWidgetOwner() { return WidgetOwner; };

protected:

	virtual void NativeConstruct() override;

protected:

	UPROPERTY()
	AActor* WidgetOwner;

	UPROPERTY()
	class UWorldSubsystem_GlobalEvents* WS_GlobalEvents;

};
