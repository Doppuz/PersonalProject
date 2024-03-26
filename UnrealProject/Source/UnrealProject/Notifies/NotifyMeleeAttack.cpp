// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyMeleeAttack.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Characters/MainCharacter.h"
#include "../Library/QuickAccessLibrary.h"

void UNotifyMeleeAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp)
	{
		ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(MeshComp->GetOwner());

		if (BaseCharacter && BaseCharacter->HasAuthority())
		{
			FHitResult HitResult;
			FVector StartLocation = BaseCharacter->GetActorLocation();
			FVector EndLocation = BaseCharacter->GetActorLocation() + BaseCharacter->GetActorForwardVector() * AttackRange;
			UKismetSystemLibrary::SphereTraceSingle(BaseCharacter, StartLocation, EndLocation, AttackRadius, UEngineTypes::ConvertToTraceType(ECC_Pawn), true,
				TArray<AActor*> {BaseCharacter}, EDrawDebugTrace::None, HitResult, true);

			if (HitResult.bBlockingHit)
			{
				AActor* HitActor = HitResult.GetActor();

				if (HitActor)
				{
					QL::ApplyDamageToActor(BaseCharacter, HitActor, Damage);
				}
			}
		}
	}
}