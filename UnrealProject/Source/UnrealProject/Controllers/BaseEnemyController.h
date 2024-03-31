// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAIController.h"
#include "../Enums/Enums_AI.h"
#include "BaseEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API ABaseEnemyController : public ABaseAIController
{
	GENERATED_BODY()
	
protected:

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	void OnTargetPerceptionForgotten(AActor* Actor);

	virtual void SetUpInitialValues();

#pragma region Senses

protected:

	void HandleSightSense(AActor* Actor, FAIStimulus Stimulus);

	void HandleHearingSense(AActor* Actor, FAIStimulus Stimulus);

#pragma endregion

#pragma region EnemyState

public:

	UFUNCTION(BlueprintCallable, Category = "EnemyState")
	void SetCurrentEnemyState(EEnemyState InCurrentEnemyState);

	UFUNCTION(BlueprintPure, Category = "EnemyState")
	EEnemyState GetCurrentEnemyState();

#pragma endregion

#pragma region Attacktarget

public:

	UFUNCTION(BlueprintCallable, Category = "EnemyState")
	void SetCurrentAttackTarget(AActor* NewTarget);

	UFUNCTION(BlueprintPure, Category = "EnemyState")
	AActor* GetCurrentAttackTarget();

#pragma endregion

};
