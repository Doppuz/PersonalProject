// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"	
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Library/QuickAccessLibrary.h"
#include "../Characters/MainCharacter.h"	
#include "Perception/AIPerceptionComponent.h"
#include <Perception/AISenseConfig_Sight.h>
#include <Perception/AISenseConfig_Hearing.h>

ABaseAIController::ABaseAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	SetPerceptionComponent(*AIPerceptionComponent);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SightConfig->SightRadius = 900.0f;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 150.0f;
	SightConfig->PeripheralVisionAngleDegrees = 60.0f;
	SightConfig->SetMaxAge(15.0f);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	GetPerceptionComponent()->ConfigureSense(*SightConfig);

	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
	HearingConfig->HearingRange = 1200.0f;
	HearingConfig->LoSHearingRange = 1500.0f;

	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;

	GetPerceptionComponent()->ConfigureSense(*HearingConfig);

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunBehaviorTree(BehaviorTree);

	if (Blackboard)
	{
		Blackboard->SetValueAsObject("AttackTarget", UQuickAccessLibrary::GetPlayer(this));
	}
}

void ABaseAIController::HandleSightSense(AActor* Actor, FAIStimulus Stimulus)
{
	//Override in children
}

void ABaseAIController::HandleHearingSense(AActor* Actor, FAIStimulus Stimulus)
{
	//Override in children
}

void ABaseAIController::HandleOutOfSightSense(AActor* Actor, FAIStimulus Stimulus)
{
	//Override in children
}

void ABaseAIController::HandleHearingExpiresSense(AActor* Actor, FAIStimulus Stimulus)
{
	//Override in children
}
