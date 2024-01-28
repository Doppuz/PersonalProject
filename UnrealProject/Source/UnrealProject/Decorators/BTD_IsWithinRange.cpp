// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_IsWithinRange.h"
#include "../Controllers/BaseEnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UBTD_IsWithinRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bSuccess = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	if (!bSuccess) return false;

	ABaseEnemyController* BaseEnemyController = Cast<ABaseEnemyController>(OwnerComp.GetAIOwner());

	if (BaseEnemyController)
	{
		APawn* CurrentOwner = BaseEnemyController->GetPawn();
		AActor* CurrentTarget = BaseEnemyController->GetCurrentAttackTarget();

		if (CurrentTarget && OwnerComp.GetBlackboardComponent())
		{
			float IdealRange = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(IdealRangeKey.SelectedKeyName) - 100;
			float DistancePawnTarget = FVector::Distance(CurrentTarget->GetActorLocation(), CurrentOwner->GetActorLocation());

			if (DistancePawnTarget <= IdealRange)
			{
				return true;
			}
		}
	}

	return false;
}
