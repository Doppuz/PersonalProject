// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreUI.h"
#include "../../Subsystem/WorldSubsystem/WorldSubsystem_GlobalEvents.h"	
#include "Components/TextBlock.h"

void UScoreUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (ensureAlways(WS_GlobalEvents))
	{
		WS_GlobalEvents->OnScoreUpdated.AddDynamic(this, &UScoreUI::OnScoreUpdated);
	}
}

void UScoreUI::NativeDestruct()
{
	Super::NativeDestruct();

	if (ensureAlways(WS_GlobalEvents))
	{
		WS_GlobalEvents->OnScoreUpdated.RemoveDynamic(this, &UScoreUI::OnScoreUpdated);
	}
}

void UScoreUI::OnScoreUpdated(float OldScore, float NewScore)
{
	CurrentScoreText->SetText(FText::FromString("Score: "+FString::FromInt(NewScore)));
}
