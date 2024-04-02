// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementManager.h"
#include "../../Interfaces/MovementInterface.h"
#include "Net/UnrealNetwork.h"

UMovementManager::UMovementManager()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
}

void UMovementManager::SetCurrentMovementState(EMovementState InState, bool SmoothTransition, float SmoothTransitionDuration)
{
	if (!GetOwner()->HasAuthority())
	{
		return;
	}

	if (CurrentMovementState == InState)
	{
		return;
	}

	if (SmoothTransition)
	{
		InitialValueTransition = MovementStateSpeed[(uint8)CurrentMovementState];
		FinalValueTransition = MovementStateSpeed[(uint8)InState];
		SmoothSpeedForSecond = (FinalValueTransition - InitialValueTransition) / SmoothTransitionDuration;

		CurrentMovementState = InState;

		SetComponentTickEnabled(true);
	}
	else
	{
		SetComponentTickEnabled(false);
		CurrentMovementState = InState;
		if (ensureAlways(OwnerMovementInterface))
		{
			OwnerMovementInterface->SetMaxMovementSpeed(MovementStateSpeed[(uint8)InState]);
		}
	}
}

// Called when the game starts
void UMovementManager::BeginPlay()
{
	Super::BeginPlay();

	OwnerMovementInterface = Cast<IMovementInterface>(GetOwner());

	SetComponentTickEnabled(false);
}

void UMovementManager::OnRep_CurrentMovementState()
{
	if (ensureAlways(OwnerMovementInterface))
	{
		OwnerMovementInterface->SetMaxMovementSpeed(MovementStateSpeed[(uint8)CurrentMovementState]);
	}
}

void UMovementManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ensureAlways(OwnerMovementInterface) && GetOwner()->HasAuthority())
	{
		float Current = OwnerMovementInterface->GetCurrentMaxMovementSpeed();

		float NewMovementSpeed = 0.f;
		if (InitialValueTransition <= FinalValueTransition)
		{
			NewMovementSpeed = FMath::Clamp(Current + SmoothSpeedForSecond * DeltaTime, InitialValueTransition, FinalValueTransition);
		}
		else
		{
			NewMovementSpeed = FMath::Clamp(Current + SmoothSpeedForSecond * DeltaTime, FinalValueTransition, InitialValueTransition);
		}

		OwnerMovementInterface->SetMaxMovementSpeed(NewMovementSpeed);

		if (NewMovementSpeed == FinalValueTransition)
		{
			InitialValueTransition = 0.f;
			FinalValueTransition = 0.f;
			SmoothSpeedForSecond = 0.f;

			SetComponentTickEnabled(false);
		}
	}
}

#pragma region Replication

void UMovementManager::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMovementManager, CurrentMovementState);
}

#pragma endregion