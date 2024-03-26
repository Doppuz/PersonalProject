// Fill out your copyright notice in the Description page of Project Settings.


#include "Stat_Health.h"
#include "../../Components/GeneralComponents/ActionComponent.h"
#include "../../Components/GeneralComponents/StatsManager.h"
#include "../../Characters/BaseCharacter.h"
#include "../../Library/QuickAccessLibrary.h"

FStat_Broadcast UStat_Health::ChangeStat(AActor* Instigator, float Value)
{
	if (ensure(StatsManagerRef) && ensure(StatsManagerRef->GetOwner()) && StatsManagerRef->GetOwner()->HasAuthority())
	{
		if (Value < 0)
		{
			float DamageAmount = Value;
			float CurrentShield = StatsManagerRef->GetCurrentStatValue(EStatCategory::SHIELD);

			StatsManagerRef->ChangeStat(Instigator, EStatCategory::SHIELD, DamageAmount);
			if (CurrentShield > 0)
			{
				DamageAmount += CurrentShield;

				if (DamageAmount >= 0)
				{
					return FStat_Broadcast();
				}
				else
				{
					return Super::ChangeStat(Instigator, DamageAmount);
				}
			}
		}
		
		return Super::ChangeStat(Instigator, Value);
	}

	return FStat_Broadcast();
}

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
				ActionComponent->AddAction_Soft(Instigator, DieAction);
			}
		}
	}
}
