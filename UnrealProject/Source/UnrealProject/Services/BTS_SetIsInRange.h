// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_SetIsInRange.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UBTS_SetIsInRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
protected:

	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	void SetIsInRange(UBehaviorTreeComponent& OwnerComp);

protected:

	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector TargetRangeKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector IsRangeKey;

};
