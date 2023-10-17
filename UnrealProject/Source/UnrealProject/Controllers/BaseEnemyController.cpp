// Fill out your copyright notice in the Description page of Project Settings.

#include "BehaviorTree/BlackboardComponent.h"
#include "BaseEnemyController.h"
#include "Perception/AIPerceptionComponent.h"
#include <Perception/AISenseConfig_Sight.h>
#include <Perception/AISenseConfig_Hearing.h>
#include "../Characters/MainCharacter.h"

void ABaseEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseEnemyController::OnTargetPerceptionUpdated);
	AIPerceptionComponent->OnTargetPerceptionForgotten.AddDynamic(this, &ABaseEnemyController::OnTargetPerceptionForgotten);
}

void ABaseEnemyController::OnUnPossess()
{
	AIPerceptionComponent->OnTargetPerceptionUpdated.RemoveDynamic(this, &ABaseEnemyController::OnTargetPerceptionUpdated);
	AIPerceptionComponent->OnTargetPerceptionForgotten.RemoveDynamic(this, &ABaseEnemyController::OnTargetPerceptionForgotten);
}

void ABaseEnemyController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor && !Actor->GetClass()->IsChildOf(AMainCharacter::StaticClass()))
	{
		//to be changed
		return;
	}

	UAISenseConfig* CurrentAISenseConfig = AIPerceptionComponent->GetSenseConfig(Stimulus.Type);

	if (Stimulus.WasSuccessfullySensed())
	{
		if (CurrentAISenseConfig)
		{
			if (CurrentAISenseConfig->GetClass() == SightConfig->GetClass())
			{
				HandleSightSense(Actor, Stimulus);
			}
			else if (CurrentAISenseConfig->GetClass() == HearingConfig->GetClass())
			{
				HandleHearingSense(Actor, Stimulus);
			}
		}
	}
	else
	{
		if (CurrentAISenseConfig)
		{
			if (CurrentAISenseConfig->GetClass() == SightConfig->GetClass())
			{
				HandleOutOfSightSense(Actor, Stimulus);
			}
			else if (CurrentAISenseConfig->GetClass() == HearingConfig->GetClass())
			{
				HandleHearingExpiresSense(Actor, Stimulus);
			}
		}
	}
}

void ABaseEnemyController::OnTargetPerceptionForgotten(AActor* Actor)
{
	EEnemyState EnemyState = GetCurrentEnemyState();

	switch (EnemyState)
	{
	case EEnemyState::PASSIVE:
	case EEnemyState::ATTACKING:
	case EEnemyState::INVESTIGATING:
		SetCurrentEnemyState(EEnemyState::PASSIVE);
		break;
	case EEnemyState::MAX:
		break;
	default:
		break;
	}
}

void ABaseEnemyController::HandleSightSense(AActor* Actor, FAIStimulus Stimulus)
{
	EEnemyState EnemyState = GetCurrentEnemyState();

	switch (EnemyState)
	{
	case EEnemyState::PASSIVE:

		SetCurrentAttackTarget(Actor);
		SetCurrentEnemyState(EEnemyState::ATTACKING);

		break;
	case EEnemyState::ATTACKING:
		break;
	case EEnemyState::INVESTIGATING:

		SetCurrentEnemyState(EEnemyState::ATTACKING);

		break;
	case EEnemyState::MAX:
		break;
	default:
		break;
	}
}

void ABaseEnemyController::HandleHearingSense(AActor* Actor, FAIStimulus Stimulus)
{
	EEnemyState EnemyState = GetCurrentEnemyState();

	if (GetBlackboardComponent()&& Actor)
	{
		GetBlackboardComponent()->SetValueAsVector("NoisePoint", Actor->GetActorLocation());
	}

	switch (EnemyState)
	{
	case EEnemyState::PASSIVE:

		SetCurrentEnemyState(EEnemyState::INVESTIGATING);

		break;
	case EEnemyState::ATTACKING:
		break;
	case EEnemyState::INVESTIGATING:
		break;
	case EEnemyState::MAX:
		break;
	default:
		break;
	}
}

#pragma region EnemyState

void ABaseEnemyController::SetCurrentEnemyState(EEnemyState InCurrentEnemyState)
{
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();

	if (BlackboardComponent)
	{
		BlackboardComponent->SetValueAsEnum("EnemyState", (uint8)InCurrentEnemyState);
	}
}

EEnemyState ABaseEnemyController::GetCurrentEnemyState()
{
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();

	if (BlackboardComponent)
	{
		return (EEnemyState) BlackboardComponent->GetValueAsEnum("EnemyState");
	}

	return EEnemyState::MAX;
}

#pragma endregion

#pragma region Attacktarget

void ABaseEnemyController::SetCurrentAttackTarget(AActor* NewTarget)
{
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();

	if (BlackboardComponent)
	{
		BlackboardComponent->SetValueAsObject("AttackTarget", NewTarget);
	}
}

AActor* ABaseEnemyController::GetCurrentAttackTarget()
{
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();

	if (BlackboardComponent)
	{
		return Cast<AActor>(BlackboardComponent->GetValueAsObject("AttackTarget"));
	}

	return nullptr;
}

#pragma endregion