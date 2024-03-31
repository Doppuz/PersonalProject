// Fill out your copyright notice in the Description page of Project Settings.


#include "AddWidgetAction.h"	
#include "../../UI/GeneralUserWidget.h"
#include "../../Components/GeneralComponents/ActionComponent.h"

void UAddWidgetAction::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ENetRole LocalRole = ActionComponentOwner->GetOwner()->GetLocalRole();
	APawn* CurrentPawn = Cast<APawn>(ActionComponentOwner->GetOwner());

	if (ensureAlways(ActionComponentOwner) && CurrentPawn && CurrentPawn->IsLocallyControlled())
	{
		UGeneralUserWidget* NewWidget = CreateWidget<UGeneralUserWidget>(GetWorld(), WidgetToAdd);

		if (ensureAlways(NewWidget))
		{
			NewWidget->SetWidgetOwner(ActionComponentOwner->GetOwner());
			NewWidget->AddToViewport();

			//Ask the server to stop the action
			ActionComponentOwner->ServerStopAction(Instigator, ActionName);

			//If I am a client, simulate the stop of the action
			if (LocalRole != ENetRole::ROLE_Authority)
			{
				StopAction_Implementation(Instigator);
			}
		}
	}
}

void UAddWidgetAction::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);

	if (ensureAlways(ActionComponentOwner))
	{
		ActionComponentOwner->RemoveAction(ActionComponentOwner->GetOwner(), this);
	}
}
