// Fill out your copyright notice in the Description page of Project Settings.


#include "DTEnemySpawnAction.h"
#include "Engine/AssetManager.h"
#include "../../../DataAsset/AI/PDA_EnemyAI.h"
#include "../../../Components/GeneralComponents/ActionComponent.h"
#include "../../../Subsystem/WorldSubsystem/WorldSubsystem_GlobalEvents.h"

bool UDTEnemySpawnAction::DataTableFilterCondition(const FPrimaryDataAssetRow* InTableRow)
{
	return true;
}

void UDTEnemySpawnAction::OnRowLoaded(FPrimaryAssetId LoadedId)
{
    UAssetManager* Manager = UAssetManager::GetIfValid();
    if (Manager)
    {
        UPDA_EnemyAI* AIData = Cast<UPDA_EnemyAI>(Manager->GetPrimaryAssetObject(LoadedId));

        if (ensureAlways(AIData) && ensureAlways(ActionComponentOwner))
        {
            if (ensureAlways(AIData->BaseEnemyClass))
            {
                AActor* NewActor = GetWorld()->SpawnActor<AActor>(AIData->BaseEnemyClass, ActionComponentOwner->GetOwner()->GetActorLocation(), ActionComponentOwner->GetOwner()->GetActorForwardVector().Rotation());
            
                if (NewActor && ensureAlways(WS_GlobalEvents))
                {
                    WS_GlobalEvents->OnActionSpawnActor.Broadcast(ActionComponentOwner, NewActor);
                }
            }
        }
    }

    Super::OnRowLoaded(LoadedId);
}
