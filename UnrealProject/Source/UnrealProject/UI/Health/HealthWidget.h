// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../UI/GeneralUserWidget.h"
#include "../../Enums/Enums_Stat.h"
#include "HealthWidget.generated.h"

class UWorldSubsystem_GlobalEvents;
class UProgressBar;

UCLASS()
class UNREALPROJECT_API UHealthWidget : public UGeneralUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	/*UFUNCTION(BlueprintCallable, Category = "Debug")
	void CreateInitialHealth(int MaxHealth);*/

protected:

	UFUNCTION()
	void OnStatChanged(FStat_Broadcast StatBroadcast);

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthProgessBar;

	UPROPERTY()
	UWorldSubsystem_GlobalEvents* WS_GlobalEvents;
};
