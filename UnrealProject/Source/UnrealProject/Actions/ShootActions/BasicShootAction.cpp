// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicShootAction.h"
#include "../../Characters/BaseCharacter.h"
#include "../../GameInstance/SAGameInstance.h"

void UBasicShootAction::OnPlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if (NotifyName == "ShootNotify")
	{
		AI->OnPlayMontageNotifyBegin.RemoveDynamic(this, &UBasicShootAction::OnPlayMontageNotifyBegin);

		if (ensureAlways(GI))
		{
			if (BasicProjectileClass)
			{
				ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(ActionRepData.Instigator);

				if (ensureAlways(BaseCharacter))
				{
					USkeletalMeshComponent* SkeletalMeshComponent = BaseCharacter->GetMesh();

					if (ensureAlways(SkeletalMeshComponent->DoesSocketExist(ShootSocket)))
					{
						FVector InstigatorForwardDirection = BaseCharacter->GetActorForwardVector();

						FVector SpawnLocation = SkeletalMeshComponent->GetSocketLocation(ShootSocket);
						FRotator SpawnRotation = InstigatorForwardDirection.Rotation();

						//Uncomment for trace debug
						//DrawDebugLine(BaseCharacter->GetWorld(), SpawnLocation, SpawnLocation + TraceDirection * 100, FColor::Blue, true, -1.f, 0U, 5.f);

						FActorSpawnParameters SpawnParameters;
						SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
						SpawnParameters.Owner = BaseCharacter;
						SpawnParameters.Instigator = BaseCharacter;

						FTransform Transform(SpawnRotation, SpawnLocation);
						GetWorld()->SpawnActor<ABasicProjectile>(BasicProjectileClass, Transform, SpawnParameters);

						StopAction(ActionRepData.Instigator);
					}
				}
			}
		}
	}
}

void UBasicShootAction::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	//Overriden old behaviour
}
