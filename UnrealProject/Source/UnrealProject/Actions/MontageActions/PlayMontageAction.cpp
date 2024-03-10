// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayMontageAction.h"
#include "../../Characters/BaseCharacter.h"
#include "../../GameInstance/SAGameInstance.h"

void UPlayMontageAction::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(Instigator);

	if (ensureAlways(BaseCharacter))
	{
		AI = BaseCharacter->GetAnimInstance();

		if (ensureAlways(AI))
		{
			if (BaseCharacter->HasAuthority())
			{
				AI->OnPlayMontageNotifyBegin.AddDynamic(this, &UPlayMontageAction::OnPlayMontageNotifyBegin);
			}

			BaseCharacter->PlayAnimMontage(MontageToPlay);
		}
	}
}

void UPlayMontageAction::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);

	if (ensureAlways(AI))
	{
		AI->OnPlayMontageNotifyBegin.RemoveDynamic(this, &UPlayMontageAction::OnPlayMontageNotifyBegin);
	}
}

void UPlayMontageAction::OnPlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	//override children
}
