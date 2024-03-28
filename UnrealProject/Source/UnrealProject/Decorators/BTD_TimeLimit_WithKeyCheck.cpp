// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_TimeLimit_WithKeyCheck.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTD_TimeLimit_WithKeyCheck::UBTD_TimeLimit_WithKeyCheck()
{
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
	bNotifyTick = true;
}

void UBTD_TimeLimit_WithKeyCheck::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	
}

void UBTD_TimeLimit_WithKeyCheck::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsFloat(TimerDurationKey.SelectedKeyName, FMath::RandRange(TimerDuration - RandomDeviation, TimerDuration + RandomDeviation));
	}
}

void UBTD_TimeLimit_WithKeyCheck::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsFloat(TimerDurationKey.SelectedKeyName, 0);
	}
}

void UBTD_TimeLimit_WithKeyCheck::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp && BlackboardComp->GetValueAsBool(TimerKey.SelectedKeyName))
	{
		float CurrentAmount = BlackboardComp->GetValueAsFloat(TimerDurationKey.SelectedKeyName);

		if (CurrentAmount <= 0)
		{
			OwnerComp.RequestExecution(this);
		}
		else
		{
			BlackboardComp->SetValueAsFloat(TimerDurationKey.SelectedKeyName, CurrentAmount - DeltaSeconds);
		}
	}
}