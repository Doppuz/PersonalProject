// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_SetIsInRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

void UBTS_SetIsInRange::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);

	SetIsInRange(SearchData.OwnerComp);
}

void UBTS_SetIsInRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	SetIsInRange(OwnerComp);
}

void UBTS_SetIsInRange::SetIsInRange(UBehaviorTreeComponent& OwnerComp)
{
	AAIController* AICOwner = OwnerComp.GetAIOwner();
	APawn* Owner = AICOwner->GetPawn();

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	
	if (BlackboardComponent)
	{
		AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(BlackboardKey.SelectedKeyName));
		float TargetRange = BlackboardComponent->GetValueAsFloat(TargetRangeKey.SelectedKeyName);

		if (TargetActor)
		{
			FVector V1 = Owner->GetActorLocation();
			FVector V2 = TargetActor->GetActorLocation();
			float ActorDistance = FVector::Distance(Owner->GetActorLocation(), TargetActor->GetActorLocation());

			if (ActorDistance < TargetRange)
			{
				BlackboardComponent->SetValueAsBool(IsRangeKey.SelectedKeyName, true);
			}
			else
			{
				BlackboardComponent->SetValueAsBool(IsRangeKey.SelectedKeyName, false);
			}
		}
	}
}
