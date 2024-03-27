// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_StartAction.h"
#include "AIController.h"
#include "../Characters/BaseCharacter.h"
#include "../Components/GeneralComponents/ActionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTT_StartAction::InitializeFromAsset(UBehaviorTree& Asset)
{
    Super::InitializeFromAsset(Asset);

    UBlackboardData* BBAsset = GetBlackboardAsset();
    if (BBAsset)
    {
        StopActionKey.ResolveSelectedKey(*BBAsset);
    }
    else
    {
        UE_LOG(LogBehaviorTree, Warning, TEXT("Can't initialize %s due to missing blackboard data."), *GetName());
        StopActionKey.InvalidateResolvedKey();
    }
}

EBTNodeResult::Type UBTT_StartAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(AIController->GetCharacter());

    if (BaseCharacter)
    {
        UActionComponent* ActionComponent = BaseCharacter->GetActionComponent();

        if (ensureAlways(ActionComponent))
        {
            if (bWaitForStopAction)
            {
                UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
                if (ensureAlways(BlackboardComp))
                {
                    BlackboardComp->SetValueAsString(StopActionKey.SelectedKeyName, "");
                 
                    auto KeyID = StopActionKey.GetSelectedKeyID();
                    BlackboardComp->RegisterObserver(KeyID, this, FOnBlackboardChangeNotification::CreateUObject(this, &UBTT_StartAction::OnBlackboardKeyValueChange));
                }
                
                ActionComponent->StartActionByName(BaseCharacter, ActionName);

                return EBTNodeResult::InProgress;
            }

            ActionComponent->StartActionByName(BaseCharacter, ActionName);

            return EBTNodeResult::Succeeded;
        }
    }

    return EBTNodeResult::Failed;
}

EBlackboardNotificationResult UBTT_StartAction::OnBlackboardKeyValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID)
{
    UBehaviorTreeComponent* BehaviorComp = (UBehaviorTreeComponent*)Blackboard.GetBrainComponent();
    if (BehaviorComp == nullptr)
    {
        return EBlackboardNotificationResult::RemoveObserver;
    }
    
    //Cannot unregister the observer form the Blackboard param
    UBlackboardComponent* BlackboardComp = BehaviorComp->GetBlackboardComponent();
    if (BlackboardComp)
    {
        if (ActionName.ToString() == BlackboardComp->GetValueAsString(StopActionKey.SelectedKeyName))
        {
            if (StopActionKey.GetSelectedKeyID() == ChangedKeyID)
            {
                BlackboardComp->UnregisterObserversFrom(this);

                FinishLatentTask(*BehaviorComp, EBTNodeResult::Succeeded);
            }
        }
    }

    return EBlackboardNotificationResult::ContinueObserving;
}