// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_TimeLimit_WithKeyCheck.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UBTD_TimeLimit_WithKeyCheck : public UBTDecorator
{
	GENERATED_BODY()
	
public:

	UBTD_TimeLimit_WithKeyCheck();

protected:

	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:

	UPROPERTY(EditAnywhere, Category = Timer)
	float TimerDuration = 5.f;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector TimerDurationKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector TimerKey;

};
