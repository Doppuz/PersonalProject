// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickAccessLibrary.h"
#include "../GameInstance/ShooterGameInstance.h"
#include "../Characters/MainCharacter.h"

UShooterGameInstance* UQuickAccessLibrary::GetGameInstance(UObject* WorldContextObject)
{
	if (!WorldContextObject)
	{
		return nullptr;
	}

	UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);

	return Cast<UShooterGameInstance>(World->GetGameInstance());
}

AMainCharacter* UQuickAccessLibrary::GetPlayer(UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);

	if (ensure(World))
	{
		APlayerController* PC = World->GetFirstPlayerController();
		if (PC)
		{
			AMainCharacter* curChar = Cast<AMainCharacter>(PC->GetPawn());
			return curChar;
		}
	}

	return nullptr;
}

