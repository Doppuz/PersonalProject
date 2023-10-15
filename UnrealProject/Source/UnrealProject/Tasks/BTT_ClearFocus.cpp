// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_ClearFocus.h"
#include "AIController.h"

EBTNodeResult::Type UBTT_ClearFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

	if (AIController && BlackboardComponent)
	{
		AIController->ClearFocus(EAIFocusPriority::Default);
	}

	return EBTNodeResult::Succeeded;
}
