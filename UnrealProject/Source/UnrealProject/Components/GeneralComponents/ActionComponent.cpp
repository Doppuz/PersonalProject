// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionComponent.h"
#include "../../Library/QuickAccessLibrary.h"
#include "../../GameInstance/SAGameInstance.h"
#include "../../Actions/Action.h"
#include "../../Library/QuickAccessLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"

UActionComponent::UActionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);
}


// Called when the game starts
void UActionComponent::BeginPlay()
{
	Super::BeginPlay();

	GI = UQuickAccessLibrary::GetGameInstance(GetOwner());

	if (GetOwner()->HasAuthority())
	{
		for (int i = 0; i < DefaultActions.Num(); i++)
		{
			AddAction(GetOwner(), DefaultActions[i]);
		}
	}
}

void UActionComponent::AddAction(AActor* Instigator, TSoftClassPtr<UAction> SoftActionClass)
{
	//Return if not the server
	if (!GetOwner()->HasAuthority())
	{
		return;
	}

	if (ensureAlways(GI))
	{
		GI->StreamableManager.RequestAsyncLoad(SoftActionClass.ToSoftObjectPath(), [this, Instigator, SoftActionClass]()
			{
				TSubclassOf<UAction> ActionClass = SoftActionClass.Get();

				if (ActionClass)
				{
					UAction* NewAction = NewObject<UAction>(this, ActionClass);

					if (NewAction)
					{
						CurrentActions.Add(NewAction);
						
						NewAction->Initialize(this);

						if (NewAction->GetAutoPlay() && NewAction->CanStart())
						{
							NewAction->StartAction(Instigator);
						}
					}
				}
			});
	}
}

void UActionComponent::RemoveAction(AActor* Instigator, UAction* ActionToRemove)
{	
	//Return if not the server
	if (!GetOwner()->HasAuthority())
	{
		return;
	}

	for (int i = 0; i < CurrentActions.Num(); i++)
	{
		if (CurrentActions[i] == ActionToRemove)
		{
			CurrentActions.RemoveAt(i);
			return;
		}
	}
}

void UActionComponent::StartActionByName(AActor* Instigator, FGameplayTag ActionName)
{
	for (int i = 0; i < CurrentActions.Num(); i++)
	{
		if (CurrentActions[i]->GetActionName() == ActionName)
		{
			if (!CurrentActions[i]->CanStart())
			{
				if (GEngine)
				{
					FString FailedMsg = FString::Printf(TEXT("Failed to run: %s"), *ActionName.ToString());
					GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FailedMsg);
				}
				continue;
			}

			// If I am the client
			if (!GetOwner()->HasAuthority())
			{
				ServerStartAction(Instigator, ActionName);
			}

			CurrentActions[i]->StartAction(Instigator);
		}
	}
}

void UActionComponent::StopActionByName(AActor* Instigator, FGameplayTag ActionName)
{
	for (int i = 0; i < CurrentActions.Num(); i++)
	{
		if (CurrentActions[i]->GetActionName() == ActionName)
		{
			if (!CurrentActions[i]->GetIsRunning())
			{
				if (GEngine)
				{
					FString FailedMsg = FString::Printf(TEXT("Failed to run: %s"), *ActionName.ToString());
					GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FailedMsg);
				}
				continue;
			}

			// If I am the client
			if (!GetOwner()->HasAuthority())
			{
				ServerStopAction(Instigator, ActionName);
			}

			CurrentActions[i]->StopAction(Instigator);
		}
	}
}

UAction* UActionComponent::GetAction(TSoftClassPtr<UAction> ActionSoftClass)
{
	for (int i = 0; i < CurrentActions.Num(); i++)
	{
		if (CurrentActions[i] && QL::SoftClassIsChildOf(ActionSoftClass, CurrentActions[i]->GetClass()))
		{
			return CurrentActions[i];
		}
	}

	return nullptr;
}

#pragma region Server

void UActionComponent::ServerStartAction_Implementation(AActor* Instigator, FGameplayTag ActionName)
{
	StartActionByName(Instigator, ActionName);
}

void UActionComponent::ServerStopAction_Implementation(AActor* Instigator, FGameplayTag ActionName)
{
	StartActionByName(Instigator, ActionName);
}

#pragma endregion

#pragma region Replication

void UActionComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UActionComponent, CurrentActions);
}

bool UActionComponent::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
	for (UAction* Action : CurrentActions)
	{
		if (Action)
		{
			WroteSomething |= Channel->ReplicateSubobject(Action, *Bunch, *RepFlags);
		}
	}

	return WroteSomething;
}

#pragma endregion