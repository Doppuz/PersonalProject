// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleSpawnAction.h"
#include "../../Components/GeneralComponents/ActionComponent.h"
#include "../../GameInstance/SAGameInstance.h"

void USingleSpawnAction::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	if (ensureAlways(ActionComponentOwner) && ActionComponentOwner->GetOwner()->HasAuthority())
	{
		if (ensureAlways(GI))
		{
			GI->StreamableManager.RequestAsyncLoad(SoftClassToSpawn.ToSoftObjectPath(), [this, Instigator]()
				{
					TSubclassOf<AActor> ClassToSpawn = SoftClassToSpawn.Get();

					if (ensureAlways(ClassToSpawn))
					{
						AActor* NewActor = GetWorld()->SpawnActor<AActor>(ClassToSpawn, ActionComponentOwner->GetOwner()->GetActorLocation(), ActionComponentOwner->GetOwner()->GetActorForwardVector().Rotation());
					}

					StopAction_Implementation(Instigator);
				});
		}
	}
}

void USingleSpawnAction::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);
}
