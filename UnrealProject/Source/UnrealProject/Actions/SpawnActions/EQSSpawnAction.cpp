// Fill out your copyright notice in the Description page of Project Settings.


#include "EQSSpawnAction.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "../../Components/GeneralComponents/ActionComponent.h"

void UEQSSpawnAction::OnSpawnQueryFinished(TSharedPtr<FEnvQueryResult> Result)
{
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	AActor* NewActor = GetWorld()->SpawnActor<AActor>(ClassToSpawn, Result->GetItemAsLocation(0), ActionComponentOwner->GetOwner()->GetActorForwardVector().Rotation(), ActorSpawnParameters);
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
