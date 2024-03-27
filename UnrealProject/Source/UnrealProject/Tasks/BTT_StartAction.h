// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GameplayTagContainer.h"
#include "BTT_StartAction.generated.h"

UCLASS()
class UNREALPROJECT_API UBTT_StartAction : public UBTTaskNode
{
	GENERATED_BODY()

protected:

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual EBlackboardNotificationResult OnBlackboardKeyValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID);

protected:

	//Name of the action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	FGameplayTag ActionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action", meta = (EditCondition = "bWaitForStopAction", EditConditionHides))
	FBlackboardKeySelector StopActionKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	bool bWaitForStopAction = true;

};
