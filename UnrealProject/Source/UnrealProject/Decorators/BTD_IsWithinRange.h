// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BTD_IsWithinRange.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UBTD_IsWithinRange : public UBTDecorator
{
	GENERATED_BODY()
	
public:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Range")
	FBlackboardKeySelector IdealRangeKey;

};
