// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldSubsystem_GameManager.h"
#include "../../Settings/GameSubsystemSettings.h"
#include "../../Library/QuickAccessLibrary.h"
#include "../../Spawners/Spawner.h"
#include "Engine/AssetManager.h"

static int DebugPrintSpawners = 0;
FAutoConsoleVariableRef CVarDebugPrintSpawners(TEXT("DebugPrintSpawners"), DebugPrintSpawners, TEXT("Print spawners controlled by the Game Manager"), ECVF_Cheat);

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

    if (DebugPrintSpawners > 0 && GEngine && GameSubsystemSettings)
    {
        PrintSpawners(DeltaTime);
    }
}

void UWorldSubsystem_GameManager::UpdateManager()
{
    if (ensureAlways(GameSubsystemSettings))
    {
        TArray<TSoftObjectPtr<ASpawner>> CurrentRangeSpawner = GameSubsystemSettings->RangeSpawners;

        for (int i = CurrentRangeSpawner.Num() - 1; i >= 0; i--)
        {
            ASpawner* CurrentSpawner = CurrentRangeSpawner[i].Get();
            if (!CurrentSpawner || !CurrentSpawner->CanSpawn())
            {
                CurrentRangeSpawner.RemoveAt(i);
            }
        }

        if (CurrentRangeSpawner.Num() > 0)
        {
            int NumberExtracted = FMath::RandRange(0, CurrentRangeSpawner.Num() - 1);
            ActivateSpawner(CurrentRangeSpawner[NumberExtracted], GameSubsystemSettings->SpawnActionName);
        }
    }
}

void UWorldSubsystem_GameManager::PrintSpawners(float DeltaTime)
{
    // Print all the spawner

    int CurrentFreeSpawners = 0;

    for (TSoftObjectPtr<ASpawner> SpawnerSoft : GameSubsystemSettings->RangeSpawners)
    {
        ASpawner* CurrentSpawner = SpawnerSoft.Get();
        if (CurrentSpawner)
        {
            CurrentFreeSpawners = CurrentSpawner->CanSpawn() ? CurrentFreeSpawners + 1 : CurrentFreeSpawners;
            FColor TextColor = CurrentSpawner->CanSpawn() ? FColor::Green : FColor::Red;
            FString SpawnerMsg = FString::Printf(TEXT("[%s]: %s"), *GetNameSafe(CurrentSpawner), *UEnum::GetValueAsString(CurrentSpawner->GetSpawnerType()));

            GEngine->AddOnScreenDebugMessage(-1, DeltaTime, TextColor, SpawnerMsg);
        }
    }

    GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Blue, FString::Printf(TEXT("Free spawners: %i"), CurrentFreeSpawners));
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