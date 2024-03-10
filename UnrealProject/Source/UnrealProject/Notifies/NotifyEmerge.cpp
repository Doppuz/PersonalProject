// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyEmerge.h"
#include "../Characters/MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UNotifyEmerge::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp)
	{
		ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(MeshComp->GetOwner());

		if (BaseCharacter)
		{
			MeshComp->AddLocalOffset(FVector(0.f, 0.f, 200.f));
			BaseCharacter->GetCharacterMovement()->NetworkSmoothingMode = ENetworkSmoothingMode::Exponential;
		}
	}
}
