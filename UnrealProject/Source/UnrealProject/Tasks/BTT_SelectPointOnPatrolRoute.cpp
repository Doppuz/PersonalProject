// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_SelectPointOnPatrolRoute.h"
#include "AIController.h"
#include "../Interfaces/PatrolInterface.h"
#include "../PatrolRoute/PatrolRoute.h"
#include "Tasks/AITask_MoveTo.h"
#include "../Controllers/BaseAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTT_SelectPointOnPatrolRoute::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* CurrentOwner = AIController->GetPawn();

	IPatrolInterface* PatrolInterface = Cast<IPatrolInterface>(CurrentOwner);

	if (PatrolInterface && AIController)
	{
		APatrolRoute* PatrolRoute = PatrolInterface->GetPatrolRoute();

		if (PatrolRoute)
		{
			FVector NewLocation = PatrolRoute->GetlocationAtSplinePoint();

			PatrolRoute->IncrementPatrolPoint();

			if (AIController->GetBlackboardComponent())
			{
				AIController->GetBlackboardComponent()->SetValueAsVector("PatrolLocation", NewLocation);
			}

			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}