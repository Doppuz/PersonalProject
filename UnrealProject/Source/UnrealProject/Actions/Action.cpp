// Fill out your copyright notice in the Description page of Project Settings.


#include "Action.h"
#include "../Library/QuickAccessLibrary.h"
#include "Net/UnrealNetwork.h"
#include "../Components/GeneralComponents/ActionComponent.h"

void UAction::Initialize(UActionComponent* NewActionComponent)
{
	ActionComponentOwner = NewActionComponent;

	GI = UQuickAccessLibrary::GetGameInstance(this);
	WS_GlobalEvents = GetOuter()->GetWorld()->GetSubsystem<UWorldSubsystem_GlobalEvents>();
}


bool UAction::CanStart_Implementation()
{
	if (GetIsRunning())
	{
		return false;
	}

	if (ensureAlways(ActionComponentOwner) && ActionComponentOwner->ContainsActiveGameplayTags(BlockedTags))
	{
		return false;
	}

	return true;
}

void UAction::StartAction_Implementation(AActor* Instigator)
{
	if (ActionRepData.bIsRunning)
	{
		//ensureAlwaysMsgf(false, TEXT("The action is already running!"));
		return;
	}

	if (ensureAlways(ActionComponentOwner))
	{
		ActionComponentOwner->AddActiveTags(GrantsTags);
	}

	ActionRepData.Instigator = Instigator;
	ActionRepData.bIsRunning = true;
}

void UAction::StopAction_Implementation(AActor* Instigator)
{
	if (!ActionRepData.bIsRunning)
	{
		//ensureAlwaysMsgf(false, TEXT("The action is not running!"));
		return;
	}
	if (!ensureAlways(ActionComponentOwner))
	{
		return;
	}

	ActionComponentOwner->RemoveActiveTags(GrantsTags);

	ActionRepData.Instigator = Instigator;
	ActionRepData.bIsRunning = false;

	if (bAutoRemove)
	{
		ActionComponentOwner->RemoveAction(Instigator, this);
	}
}

#pragma region Replication

void UAction::OnRep_RepActionData()
{
	if (ActionRepData.bIsRunning)
	{
		StartAction(ActionRepData.Instigator);
	}
	else
	{
		StopAction(ActionRepData.Instigator);
	}
}

void UAction::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UAction, ActionRepData);
	DOREPLIFETIME(UAction, ActionComponentOwner);
}

#pragma endregion