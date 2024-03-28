// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementInterface.h"
#include "../Components/GeneralComponents/MovementManager.h"

// Add default functionality here for any IMovementInterfaces functions that are not pure virtual.

void IMovementInterface::SetCurrentMovementState(EMovementState InState, bool SmoothTransition, float SmoothTransitionDuration)
{
	if (GetMovementManager())
	{
		GetMovementManager()->SetCurrentMovementState(InState, SmoothTransition, SmoothTransitionDuration);
	}
}
