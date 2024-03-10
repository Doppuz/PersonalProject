// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_StartAction.h"
#include "AIController.h"
#include "../Characters/BaseCharacter.h"
#include "../Components/GeneralComponents/ActionComponent.h"

EBTNodeResult::Type UBTT_StartAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(AIController->GetCharacter());

    if (BaseCharacter)
    {
        UActionComponent* ActionComponent = BaseCharacter->GetActionComponent();

        if (ActionComponent)
        {
            ActionComponent->StartActionByName(BaseCharacter, ActionName);

            return EBTNodeResult::Succeeded;
        }
    }

    return EBTNodeResult::Failed;
}
