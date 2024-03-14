// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldSubsystem_GameManager.h"
#include "../../Settings/GameSubsystemSettings.h"
#include "../../Library/QuickAccessLibrary.h"
#include "../../Spawners/Spawner.h"
#include "Engine/AssetManager.h"

bool UWorldSubsystem_GameManager::ShouldCreateSubsystem(UObject* Outer) const
{
    if (!Super::ShouldCreateSubsystem(Outer))
    {
        return false;
    }

    UWorld* World = Cast<UWorld>(Outer);
    
    if (World)
    {
        TEnumAsByte<EWorldType::Type> type = World->WorldType;
        bool IsValidType = type != EWorldType::Editor && type != EWorldType::EditorPreview && type != EWorldType::None;

        if (IsValidType)
        {
            return World->GetNetMode() < NM_Client;
        }
    }

    return false;
}

void UWorldSubsystem_GameManager::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    GameSubsystemSettings = GetDefault<UGameSubsystemSettings>();
}

void UWorldSubsystem_GameManager::Tick(float DeltaTime)
{
    CurrentTick += DeltaTime;

    if (CurrentTick > CheckFrequency)
    {
        UpdateManager();

        CurrentTick = 0.f;
    }
}

void UWorldSubsystem_GameManager::UpdateManager()
{
    if (ensureAlways(GameSubsystemSettings))
    {
        int NumberExtracted = FMath::RandRange(0, GameSubsystemSettings->RangeSpawners.Num() - 1);

        ActivateSpawner(GameSubsystemSettings->RangeSpawners[NumberExtracted], GameSubsystemSettings->SpawnActionName);
    }
}

void UWorldSubsystem_GameManager::ActivateSpawner(TSoftObjectPtr<ASpawner> InSpawner, FGameplayTag ActionName)
{
    ASpawner* CurrentSpawner = InSpawner.Get();

    if (ensureAlways(CurrentSpawner))
    {
        QL::StartAction(this, CurrentSpawner, CurrentSpawner, ActionName);
    }
}

TStatId UWorldSubsystem_GameManager::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT(UMapGridTickableWorldSubsystem, STATGROUP_Tickables);
}