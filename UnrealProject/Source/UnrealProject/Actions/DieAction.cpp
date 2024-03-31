// Fill out your copyright notice in the Description page of Project Settings.


#include "DieAction.h"
#include "../Characters/BaseCharacter.h"
#include "../GameInstance/SAGameInstance.h"
#include "../Components/GeneralComponents/ActionComponent.h"
#include "../Subsystem/WorldSubsystem/WorldSubsystem_GlobalEvents.h"
#include "../Controllers/BaseAIController.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimInstance.h"

UDieAction::UDieAction()
{
	bAutoPlay = true;
}

void UDieAction::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	if (ensureAlways(ActionComponentOwner) && ActionComponentOwner->GetOwner()->HasAuthority())
	{
		ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(ActionComponentOwner->GetOwner());

		if (BaseCharacter)
		{
			ABaseAIController* BaseAIController = Cast<ABaseAIController>(BaseCharacter->GetController());
			if (BaseAIController)
			{
				BaseAIController->StopBehaviorTree();
				BaseAIController->SetFocus(nullptr);
			}

			UAnimInstance* AnimInstance = BaseCharacter->GetAnimInstance();

			if (AnimInstance)
			{
				BaseCharacter->StopAnimMontage(BaseCharacter->GetAnimInstance()->GetCurrentActiveMontage());
			}
		}

		GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, this, &UDieAction::OnEndTimer, DeadTimerDuration);
	}

}

void UDieAction::OnEndTimer()
{
	//Overriden old behaviour
	if (ensureAlways(WS_GlobalEvents) && ensureAlways(ActionComponentOwner))
	{
		WS_GlobalEvents->OnActionActorDead.Broadcast(ActionComponentOwner, ActionComponentOwner->GetOwner());
	}
}
