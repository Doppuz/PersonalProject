// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_SetClosestAttackEnemy.h"
#include "../Library/QuickAccessLibrary.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Limits.h"
#include "../GameState/SAGameStateBase.h"

EBTNodeResult::Type UBTT_SetClosestAttackEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

	if (AIController && BlackboardComponent)
	{
		AActor* Owner = AIController->GetPawn();
		AGameStateBase* GS = QL::GetGameState(this);

		if (ensureAlways(GS) && Owner)
		{
			TArray<TObjectPtr<APlayerState>> PlayerStates = GS->PlayerArray;

			if (PlayerStates.Num() > 0)
			{
				AActor* CurrentTarget = PlayerStates[0]->GetPlayerController()->GetPawn();
				float CurrentDistance = LONG_MAX;
				if (CurrentTarget)
				{
					CurrentDistance = FVector::Distance(Owner->GetActorLocation(), CurrentTarget->GetActorLocation());
				}

				for (int i = 1; i < PlayerStates.Num(); i++)
				{
					if (PlayerStates[i])
					{
						APlayerController* PlayerController = PlayerStates[i]->GetPlayerController();

						if (PlayerController)
						{
							AActor* CurrentPlayer = PlayerController->GetPawn();

							if (CurrentPlayer)
							{
								float NewDistance = FVector::Distance(Owner->GetActorLocation(), CurrentPlayer->GetActorLocation());
								if (NewDistance < CurrentDistance)
								{
									CurrentTarget = CurrentPlayer;
									CurrentDistance = NewDistance;
								}
							}
						}
					}
				}

				BlackboardComponent->SetValueAsObject("AttackTarget", CurrentTarget);
			}
		}

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
