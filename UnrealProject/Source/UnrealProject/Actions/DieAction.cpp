// Fill out your copyright notice in the Description page of Project Settings.


#include "DieAction.h"
#include "../Characters/BaseCharacter.h"
#include "../GameInstance/SAGameInstance.h"
#include "../Components/GeneralComponents/ActionComponent.h"
#include "../Subsystem/WorldSubsystem/WorldSubsystem_GlobalEvents.h"

UDieAction::UDieAction()
{
	bAutoPlay = true;
}

void UDieAction::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	//Overriden old behaviour
	if (ensureAlways(WS_GlobalEvents) && ensureAlways(ActionComponentOwner))
	{
		WS_GlobalEvents->OnActionActorDead.Broadcast(ActionComponentOwner, ActionComponentOwner->GetOwner());
	}
}
