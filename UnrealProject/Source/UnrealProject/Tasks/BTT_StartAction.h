// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_StartAction.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UBTT_StartAction : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	//Name of the action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actionn")
	FGameplayTag ActionName;

};
