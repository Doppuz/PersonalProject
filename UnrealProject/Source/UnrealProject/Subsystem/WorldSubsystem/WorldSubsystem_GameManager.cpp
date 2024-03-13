// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldSubsystem_GameManager.h"
#include "../../Settings/SubsystemSettings.h"
#include "../../Library/QuickAccessLibrary.h"
#include "../../Spawners/Spawner.h"
#include "Engine/AssetManager.h"
#include "../../DataAsset/Subsystems/PDA_WS_GameManager.h"

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

    const USubsystemSettings* Settings = GetDefault<USubsystemSettings>();

    if (ensureAlways(Settings))
    {
        PDA_ID_WS_GameManager = Settings->PDA_ID_WS_GameManager;
    }
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
    if (UAssetManager* Manager = UAssetManager::GetIfValid())
    {
        TArray<FName> Bundles;
        FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &UWorldSubsystem_GameManager::OnAssetLoaded, PDA_ID_WS_GameManager);

        Manager->LoadPrimaryAsset(PDA_ID_WS_GameManager, Bundles, Delegate);
    }
}

void UWorldSubsystem_GameManager::OnAssetLoaded(FPrimaryAssetId LoadedId)
{
    UAssetManager* Manager = UAssetManager::GetIfValid();
    if (Manager)
    {
        UPDA_WS_GameManager* SubSystemData = Cast<UPDA_WS_GameManager>(Manager->GetPrimaryAssetObject(LoadedId));

        if (ensureAlways(SubSystemData))
        {
            int NumberExtracted = FMath::RandRange(0, SubSystemData->RangeSpawners.Num() - 1);

            ActivateSpawner(SubSystemData->RangeSpawners[NumberExtracted], SubSystemData->SpawnActionName);
        }
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