// Fill out your copyright notice in the Description page of Project Settings.


#include "Action.h"
#include "../Library/QuickAccessLibrary.h"
#include "Net/UnrealNetwork.h"
#include "../Components/GeneralComponents/ActionComponent.h"
#include "../Components/GeneralComponents/ActionComponent.h"
#include "../Subsystem/WorldSubsystem/WorldSubsystem_GlobalEvents.h"

void UAction::Initialize(UActionComponent* NewActionComponent)
{
	ActionComponentOwner = NewActionComponent;

	GI = UQuickAccessLibrary::GetGameInstance(this);
	WS_GlobalEvents = GetOuter()->GetWorld()->GetSubsystem<UWorldSubsystem_GlobalEvents>();
}


bool UAction::CanStart_Implementation()
{
	if (GetIsRunning() || bIsInCooldown)
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

	if (ensureAlways(WS_GlobalEvents))
	{
		WS_GlobalEvents->OnStartAction.Broadcast(ActionComponentOwner, ActionName);
	}
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

	if (CooldownAmount > 0.f)
	{
		bIsInCooldown = true;

		if (ensureAlways(GetWorld()))
		{
			GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UAction::OnCooldownExpire, CooldownAmount, false);
		}
	}

	ActionRepData.Instigator = Instigator;
	ActionRepData.bIsRunning = false;

	if (ensureAlways(WS_GlobalEvents))
	{
		WS_GlobalEvents->OnStopAction.Broadcast(ActionComponentOwner, ActionName);
	}

	if (bAutoRemove)
	{
		ActionComponentOwner->RemoveAction(Instigator, this);
	}
}

void UAction::OnCooldownExpire()
{
	bIsInCooldown = false;
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
	DOREPLIFETIME(UAction, bIsInCooldown);
}

#pragma endregion