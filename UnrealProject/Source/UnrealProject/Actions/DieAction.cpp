// Fill out your copyright notice in the Description page of Project Settings.


#include "DieAction.h"
#include "../Characters/BaseCharacter.h"
#include "../GameInstance/SAGameInstance.h"
#include "../Components/GeneralComponents/ActionComponent.h"

UDieAction::UDieAction()
{
	bAutoPlay = true;
}

void UDieAction::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	//Overriden old behaviour
}
