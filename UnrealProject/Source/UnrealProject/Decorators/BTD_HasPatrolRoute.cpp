// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_HasPatrolRoute.h"
#include "AIController.h"
#include "../Interfaces/PatrolInterface.h"
#include "BTD_HasPatrolRoute.h"

bool UBTD_HasPatrolRoute::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bSuccess = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	
	if (!bSuccess) return false;

	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* CurrentOwner = AIController->GetPawn();

	IPatrolInterface* CurrentOwnerPatrolinterface = Cast<IPatrolInterface>(CurrentOwner);
	
	if (CurrentOwnerPatrolinterface)
	{
		if (CurrentOwnerPatrolinterface->GetPatrolRoute())
		{
			return true;
		}
	}

	return false;
}
