// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GeneralUserWidget.h"
#include "ScoreUI.generated.h"

class UTextBlock;

UCLASS()
class UNREALPROJECT_API UScoreUI : public UGeneralUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnScoreUpdated(float OldScore, float NewScore);
	
protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentScoreText;

};
