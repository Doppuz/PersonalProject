// Fill out your copyright notice in the Description page of Project Settings.


#include "EQSSpawnAction.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "../../Components/GeneralComponents/ActionComponent.h"

void UEQSSpawnAction::OnSpawnQueryFinished(TSharedPtr<FEnvQueryResult> Result)
{
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
	
	TArray<FVector> Locations;
	for (int i = 0; i < Result->Items.Num() - 1; i++)
	{
		if (Result->GetItemScore(i) > 0)
		{
			FVector CurrentLocation = Result->GetItemAsLocation(i);
			if (!Locations.Contains(CurrentLocation))
			{
				Locations.Add(CurrentLocation);
			}
		}
	}
	
	if (Locations.Num() > 0)
	{
		FVector LocationExtracted = Locations[FMath::RandRange(0, Locations.Num() - 1)];

		if (ActionComponentOwner)
		{
			LocationExtracted.Z = ActionComponentOwner->GetOwner()->GetActorLocation().Z;
		}

		AActor* NewActor = GetWorld()->SpawnActor<AActor>(ClassToSpawn, LocationExtracted, ActionComponentOwner->GetOwner()->GetActorForwardVector().Rotation(), ActorSpawnParameters);
	}
}

void UEQSSpawnAction::SpawnActor(TSubclassOf<AActor> InClassToSpawn)
{
	ClassToSpawn = InClassToSpawn;

	FEnvQueryRequest HidingSpotQueryRequest = FEnvQueryRequest(SpawnQuery, ActionComponentOwner->GetOwner());

	HidingSpotQueryRequest.Execute(
		EEnvQueryRunMode::SingleResult,
		this,
		&UEQSSpawnAction::OnSpawnQueryFinished
	);
}
