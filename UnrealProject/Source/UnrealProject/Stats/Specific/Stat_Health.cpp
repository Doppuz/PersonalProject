// Fill out your copyright notice in the Description page of Project Settings.


#include "Stat_Health.h"
#include "../../Components/GeneralComponents/ActionComponent.h"
#include "../../Components/GeneralComponents/StatsManager.h"
#include "../../Characters/BaseCharacter.h"
#include "../../Library/QuickAccessLibrary.h"

void UStat_Health::OnStatReachesMinValue_Implementation(AActor* Instigator)
{
	if (ensureAlways(StatsManagerRef))
	{
		ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(StatsManagerRef->GetOwner());

		if (ensureAlways(BaseCharacter))
		{
			UActionComponent* ActionComponent = BaseCharacter->GetActionComponent();

			if (ActionComponent)
			{
				QL::AddScoreToAllPlayers(BaseCharacter, BaseCharacter->GetCharacterScore());
				ActionComponent->AddAction(Instigator, DieAction);
			}
		}
	}
}
