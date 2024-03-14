// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayMontageAction.h"
#include "../../Characters/BaseCharacter.h"
#include "../../GameInstance/SAGameInstance.h"
#include "../../Components/GeneralComponents/ActionComponent.h"

void UPlayMontageAction::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	if (!ensureAlways(ActionComponentOwner))
	{
		return;
	}

	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(ActionComponentOwner->GetOwner());

	if (ensureAlways(BaseCharacter))
	{
		AI = BaseCharacter->GetAnimInstance();

		if (ensureAlways(AI))
		{
			if (BaseCharacter->HasAuthority())
			{
				AI->OnPlayMontageNotifyBegin.AddDynamic(this, &UPlayMontageAction::OnPlayMontageNotifyBegin);
				AI->OnMontageEnded.AddDynamic(this, &UPlayMontageAction::OnMontageEnded);
			}

			/*if (AI->IsAnyMontagePlaying())
			{
				AI->StopAllMontages(0.3f);
			}*/

			BaseCharacter->PlayAnimMontage(MontageToPlay, InitialMontageSpeed);
		}
	}
}

void UPlayMontageAction::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);

	if (ensureAlways(AI))
	{
		AI->OnPlayMontageNotifyBegin.RemoveDynamic(this, &UPlayMontageAction::OnPlayMontageNotifyBegin);
		AI->OnMontageEnded.RemoveDynamic(this, &UPlayMontageAction::OnMontageEnded);
	}
}

void UPlayMontageAction::OnPlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	//override children
}

void UPlayMontageAction::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	StopAction(ActionRepData.Instigator);
}
