// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskRangeAttack.h"
#include "AIController.h"
#include "../Interfaces/ShootInterface.h"

EBTNodeResult::Type UBTTaskRangeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* CurrentOwner = AIController->GetPawn();
	
	IShootInterface* CurrentOwnerShooterInterface = Cast<IShootInterface>(CurrentOwner);

	if (CurrentOwnerShooterInterface)
	{
		bool Result = CurrentOwnerShooterInterface->Shoot();

		if (Result)
		{
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
