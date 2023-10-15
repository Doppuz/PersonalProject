// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_SetEnemyState.h"
#include "../Controllers/BaseEnemyController.h"
#include "BTT_SetEnemyState.h"

EBTNodeResult::Type UBTT_SetEnemyState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ABaseEnemyController* AIController = Cast<ABaseEnemyController>(OwnerComp.GetAIOwner());

    if (AIController)
    {
        AIController->SetCurrentEnemyState(NewState);

        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}
