// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_SetMovementState.h"
#include "../Interfaces/MovementInterface.h"
#include "AIController.h"

EBTNodeResult::Type UBTT_SetMovementState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* CurrentOwner = AIController->GetPawn();

	IMovementInterface* CurrentOwnerMovementInterface = Cast<IMovementInterface>(CurrentOwner);

	if (CurrentOwnerMovementInterface && ensureAlways(NewMovementState != EMovementState::MAX))
	{
		CurrentOwnerMovementInterface->SetCurrentMovementState(NewMovementState, bSmoothTransition, SmoothTransitionDuration);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
