// Fill out your copyright notice in the Description page of Project Settings.


#include "DieAction.h"
#include "../Characters/BaseCharacter.h"
#include "../GameInstance/SAGameInstance.h"
#include "../Components/GeneralComponents/ActionComponent.h"

UDieAction::UDieAction()
{
	bAutoPlay = true;
}

void UDieAction::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	if (!ensureAlways(ActionComponentOwner))
	{
		return;
	}

	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(ActionComponentOwner->GetOwner());

	if (ensureAlways(BaseCharacter))
	{
		AI = BaseCharacter->GetAnimInstance();

		if (ensureAlways(AI))
		{
			//TODO: Implement score and end game UI

			BaseCharacter->PlayAnimMontage(DieMontage);
		}
	}
}

void UDieAction::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);
}
