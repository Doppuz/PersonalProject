// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickAccessLibrary.h"
#include "../GameInstance/ShooterGameInstance.h"

UShooterGameInstance* UQuickAccessLibrary::GetGameInstance(UObject* WorldContextObject)
{
	if (!WorldContextObject)
	{
		return nullptr;
	}

	UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);

	return Cast<UShooterGameInstance>(World->GetGameInstance());
}