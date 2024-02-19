// Fill out your copyright notice in the Description page of Project Settings.


#include "Action.h"

void UAction::Initialize(UActionComponent* NewActionComponent)
{
	ActionComponentOwner = NewActionComponent;
}

bool UAction::CanStart()
{
	return !bIsRunning;
}

void UAction::StartAction(AActor* Instigator)
{
	if (bIsRunning)
	{
		ensureAlwaysMsgf(false, TEXT("The action is already running!"));
		return;
	}

	bIsRunning = true;
}

void UAction::StopAction(AActor* Instigators)
{
	if (!bIsRunning)
	{
		ensureAlwaysMsgf(false, TEXT("The action is not running!"));
		return;
	}

	bIsRunning = false;
}
