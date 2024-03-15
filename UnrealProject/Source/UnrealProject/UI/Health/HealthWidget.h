// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidget.generated.h"

class UGridPanel;
class UProgressBar;

UCLASS()
class UNREALPROJECT_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	/*UFUNCTION(BlueprintCallable, Category = "Debug")
	void CreateInitialHealth(int MaxHealth);*/

protected:

	/*UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UGridPanel> HealthGrid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UProgressBar>> ProgressBars;*/

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthProgessBar;

};
