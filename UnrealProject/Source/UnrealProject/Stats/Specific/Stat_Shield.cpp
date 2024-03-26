// Fill out your copyright notice in the Description page of Project Settings.


#include "Stat_Shield.h"
#include "../../Components/GeneralComponents/ActionComponent.h"
#include "../../Components/GeneralComponents/StatsManager.h"
#include "../../Characters/BaseCharacter.h"
#include "../../Library/QuickAccessLibrary.h"
#include "../../Settings/TagsReferenceSettings.h"

void UStat_Shield::OnStatReachesMinValue_Implementation(AActor* Instigator)
{
	Super::OnStatReachesMinValue_Implementation(Instigator);

	const UTagsReferenceSettings* TagsReferenceSettings = GetDefault<UTagsReferenceSettings>();

	if (ensureAlways(StatsManagerRef) && ensureAlways(TagsReferenceSettings))
	{
		ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(StatsManagerRef->GetOwner());

		if (ensureAlways(BaseCharacter))
		{
			UActionComponent* ActionComponent = BaseCharacter->GetActionComponent();

			if (ActionComponent)
			{
				ActionComponent->StopActionByName(Instigator, TagsReferenceSettings->ShieldTag);
			}
		}
	}
}
