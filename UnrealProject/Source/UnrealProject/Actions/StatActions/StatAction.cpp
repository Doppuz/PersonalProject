// Fill out your copyright notice in the Description page of Project Settings.


#include "StatAction.h"
#include "../../Components/GeneralComponents/ActionComponent.h"
#include "../../Components/GeneralComponents/StatsManager.h"

UStatAction::UStatAction()
{
	bAutoRemove = true;
	bAutoPlay = true;
}

void UStatAction::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	if (ensureAlways(ActionComponentOwner) && ActionComponentOwner->GetOwner()->HasAuthority() && Instigator)
	{
		for (int i = 0; i < ValuesToChange.Num(); i++)
		{
			UStatsManager* CurrentStatsComponent = Cast<UStatsManager>(Instigator->FindComponentByClass(UStatsManager::StaticClass()));

			if (CurrentStatsComponent)
			{
				CurrentStatsComponent->ChangeStat(Instigator, ValuesToChange[i].StatCategory, ValuesToChange[i].Value);
			}
		}
	}

	StopAction_Implementation(Instigator);
}

void UStatAction::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);
}
