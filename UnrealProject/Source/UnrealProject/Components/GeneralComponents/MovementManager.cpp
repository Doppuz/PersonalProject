// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementManager.h"
#include "../../Interfaces/MovementInterface.h"

// Sets default values for this component's properties
UMovementManager::UMovementManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UMovementManager::SetCurrentMovementState(EMovementState InState)
{
	CurrentMovementState = InState;

	if (ensureAlways(OwnerMovementInterface))
	{
		OwnerMovementInterface->SetCurrentMovementSpeed(MovementStateSpeed[(uint8) InState]);
	}
}

// Called when the game starts
void UMovementManager::BeginPlay()
{
	Super::BeginPlay();

	OwnerMovementInterface = Cast<IMovementInterface>(GetOwner());
}