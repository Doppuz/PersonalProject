// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "../Enums/Enums_Movement.h"
#include "BTT_SetMovementState.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UBTT_SetMovementState : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere, Category = "MovementState")
	EMovementState NewMovementState = EMovementState::MAX;

};
