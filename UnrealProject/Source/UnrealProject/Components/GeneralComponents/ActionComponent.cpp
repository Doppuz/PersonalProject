// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionComponent.h"
#include "../../Library/QuickAccessLibrary.h"
#include "../../GameInstance/ShooterGameInstance.h"
#include "../../Actions/Action.h"
#include "../../Library/QuickAccessLibrary.h"

UActionComponent::UActionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UActionComponent::BeginPlay()
{
	Super::BeginPlay();

	GI = UQuickAccessLibrary::GetGameInstance(this);
}

void UActionComponent::AddAction(AActor* Instigator, TSoftClassPtr<UAction> SoftActionClass)
{
	if (ensure(GI))
	{
		GI->StreamableManager.RequestAsyncLoad(SoftActionClass.ToSoftObjectPath(), [this, Instigator, SoftActionClass]()
			{
				TSubclassOf<UAction> ActionClass = SoftActionClass.Get();

				if (ActionClass)
				{
					UAction* NewAction = NewObject<UAction>(this, ActionClass);

					if (NewAction)
					{
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
