// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleSpawnAction.h"
#include "../../Components/GeneralComponents/ActionComponent.h"
#include "../../GameInstance/SAGameInstance.h"

void USingleSpawnAction::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	if (SoftClassesToSpawn.Num() < 1)
	{
		return;
	}

	if (ensureAlways(ActionComponentOwner) && ActionComponentOwner->GetOwner()->HasAuthority())
	{
		if (ensureAlways(GI))
		{
			int RandomIndex = FMath::RandRange(0, SoftClassesToSpawn.Num() - 1);

			GI->StreamableManager.RequestAsyncLoad(SoftClassesToSpawn[RandomIndex].ToSoftObjectPath(), [this, Instigator, RandomIndex]()
				{
					TSubclassOf<AActor> ClassToSpawn = SoftClassesToSpawn[RandomIndex].Get();

					if (ensureAlways(ClassToSpawn))
					{
						SpawnActor(ClassToSpawn);
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

void USingleSpawnAction::SpawnActor(TSubclassOf<AActor> ClassToSpawn)
{
	if (GetWorld())
	{
		AActor* NewActor = GetWorld()->SpawnActor<AActor>(ClassToSpawn, ActionComponentOwner->GetOwner()->GetActorLocation(), ActionComponentOwner->GetOwner()->GetActorForwardVector().Rotation());
	}
}
