// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Focus.h"
#include "AIController.h"
#include "BTT_Focus.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTT_Focus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

	if (AIController && BlackboardComponent)
	{
		AActor* Target = Cast<AActor>(BlackboardComponent->GetValueAsObject(GetSelectedBlackboardKey()));
		AIController->SetFocus(Target);
	}

	return EBTNodeResult::Succeeded;
}
