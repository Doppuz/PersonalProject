// Fill out your copyright notice in the Description page of Project Settings.


#include "AddWidgetAction.h"	
#include "../../UI/GeneralUserWidget.h"
#include "../../Components/GeneralComponents/ActionComponent.h"

void UAddWidgetAction::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ENetRole LocalRole = ActionComponentOwner->GetOwner()->GetLocalRole();
	ENetRole RemoteRole = ActionComponentOwner->GetOwner()->GetRemoteRole();

	bool IsServerControllingThePlayer = LocalRole == ENetRole::ROLE_Authority && RemoteRole == ENetRole::ROLE_SimulatedProxy;
	bool IsClientControllingThePlayer = LocalRole == ENetRole::ROLE_AutonomousProxy;

	if (ensureAlways(ActionComponentOwner) && (IsServerControllingThePlayer || IsClientControllingThePlayer))
	{
		APlayerController* PlayerController = Cast<APlayerController>(Cast<APawn>(ActionComponentOwner->GetOwner())->GetController());
		UGeneralUserWidget* NewWidget = CreateWidget<UGeneralUserWidget>(GetWorld(), WidgetToAdd);

		if (ensureAlways(NewWidget) && ensureAlways(ActionComponentOwner))
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
