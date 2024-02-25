// Fill out your copyright notice in the Description page of Project Settings.


#include "Action.h"
#include "../Library/QuickAccessLibrary.h"

void UAction::Initialize(UActionComponent* NewActionComponent)
{
	ActionComponentOwner = NewActionComponent;

	GI = UQuickAccessLibrary::GetGameInstance(this);
}

bool UAction::CanStart_Implementation()
{
	return !bIsRunning;
}

void UAction::StartAction_Implementation(AActor* Instigator)
{
	if (bIsRunning)
	{
		ensureAlwaysMsgf(false, TEXT("The action is already running!"));
		return;
	}

	bIsRunning = true;
}

void UAction::StopAction_Implementation(AActor* Instigators)
{
	if (!bIsRunning)
	{
		ensureAlwaysMsgf(false, TEXT("The action is not running!"));
		return;
	}

	bIsRunning = false;
}
