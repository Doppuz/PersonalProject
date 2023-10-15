// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "../Enums/Enums_AI.h"
#include "BTT_SetEnemyState.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UBTT_SetEnemyState : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere, Category = "EnemyState")
	EEnemyState NewState;

};
