// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMovementManager.h"
#include "../../Characters/MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UPlayerMovementManager::UPlayerMovementManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UPlayerMovementManager::BeginPlay()
{
	Super::BeginPlay();

	MainCharacter = Cast<AMainCharacter>(GetOwner());
}

void UPlayerMovementManager::Move(const FInputActionValue& Value)
{
	if (ensure(MainCharacter))
	{
		// if x axis (as documentation suggested) input != 0
		if (!FMath::IsNearlyZero(Value[0]))
		{
			MainCharacter->AddMovementInput(MainCharacter->GetActorForwardVector(), Value[0]);
		}

		// if Y axis (as documentation suggested) input != 0
		if (!FMath::IsNearlyZero(Value[1]))
		{
			MainCharacter->AddMovementInput(MainCharacter->GetActorRightVector(), Value[1]);
		}
	}
}

void UPlayerMovementManager::RotateCamera(const FInputActionValue& Value)
{
	if (ensure(MainCharacter))
	{
		float value = Value[0];
		if (!FMath::IsNearlyZero(value))
		{
			MainCharacter->AddControllerYawInput(value * MouseSensitivityX);
		}

		value = Value[1];
		if (!FMath::IsNearlyZero(value))
		{
			MainCharacter->AddControllerPitchInput(value * MouseSensitivityY);
		}
	}
}

void UPlayerMovementManager::Jump(const FInputActionValue& Value)
{
	if (ensure(MainCharacter))
	{
		if (MainCharacter->GetCharacterMovement()->CanAttemptJump())
		{
			MainCharacter->GetCharacterMovement()->DoJump(false);
			MainCharacter->GetCharacterMovement()->bNotifyApex = true;
		}
	}
}
