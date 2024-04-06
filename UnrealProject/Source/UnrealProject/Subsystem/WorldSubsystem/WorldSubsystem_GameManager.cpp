// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldSubsystem_GameManager.h"
#include "../../Settings/GameSubsystemSettings.h"
#include "../../Settings/TagsReferenceSettings.h"
#include "../../Library/QuickAccessLibrary.h"
#include "../../Spawners/Spawner.h"
#include "Engine/AssetManager.h"
#include "../../Subsystem/WorldSubsystem/WorldSubsystem_GlobalEvents.h"
#include "../../GameState/SAGameStateBase.h"
#include "../../PlayerState/SAPlayerState.h"
#include "../../UnrealProjectGameModeBase.h"
#include "../../DataAsset/Setting/PDA_GameSubsystem.h"
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
    WS_GlobalEvents = GetWorld()->GetSubsystem<UWorldSubsystem_GlobalEvents>();
    TagsReferenceSettings = GetDefault<UTagsReferenceSettings>();

    AsyncLoadData();

    if (ensure(WS_GlobalEvents))
    {
        WS_GlobalEvents->OnAllPlayersReady.AddDynamic(this, &UWorldSubsystem_GameManager::OnAllPlayersReady);
    }
}

void UWorldSubsystem_GameManager::Tick(float DeltaTime)
{
    if (bActivateTick)
    {
        CurrentRangeEnemiesTick += DeltaTime;
        CurrentPowerUpTick += DeltaTime;
        CurrentMeleeEnemiesTick += DeltaTime;
        CurrentScoreTick += DeltaTime;
        CurrentCoinsTick += DeltaTime;
        TotalGameDuration += DeltaTime;

        if (CurrentRangeEnemiesTick >= FMath::RandRange(CheckRangeEnemiesFrequency - 2, CheckRangeEnemiesFrequency + 2))
        {
            UpdateRangeEnemiesManager();

            CurrentRangeEnemiesTick = 0.f;
        }

        if (CurrentPowerUpTick >= FMath::RandRange(PowerupCheckFrequency, CheckRangeEnemiesFrequency + 10))
        {
            UpdatePowerUpManager();

            CurrentPowerUpTick = 0.f;
        }

        if (CurrentMeleeEnemiesTick >= FMath::RandRange(CheckMeleeEnemiesFrequency, CheckMeleeEnemiesFrequency + 2))
        {
            UpdateMeleeEnemiesManager();

            CurrentMeleeEnemiesTick = 0.f;
        }

        if (CurrentCoinsTick >= CoinsCheckFrequency)
        {
            UpdateCoinsManager();

            CurrentCoinsTick = 0.f;
        }

        if (CurrentScoreTick >= ScoreCheckFrequency)
        {
            QL::AddScoreToAllPlayers(QL::GetGameState(this), CurrentScoreTick);

            CurrentScoreTick = 0.f;
        }

        if (DebugPrintSpawners > 0 && GEngine && GameSubsystemSettings)
        {
            PrintSpawners(DeltaTime);
        }
    }
}

void UWorldSubsystem_GameManager::UpdateRangeEnemiesManager()
{
    if (ensureAlways(GameSubsystemSettings) && ensureAlways(PDA_GameSubsystemSetting))
    {
        TArray<TSoftObjectPtr<ASpawner>> CurrentRangeSpawner = PDA_GameSubsystemSetting->RangeSpawners;

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
            ActivateSpawner(CurrentRangeSpawner[NumberExtracted], TagsReferenceSettings->SpawnActionName);
        }
    }
}

void UWorldSubsystem_GameManager::UpdatePowerUpManager()
{
    if (ensureAlways(GameSubsystemSettings))
    {
        TArray<TSoftObjectPtr<ASpawner>> CurrentPowerupSpawner = PDA_GameSubsystemSetting->PowerupSpawners;

        if (CurrentPowerupSpawner.Num() > 0)
        {
            int NumberExtracted = FMath::RandRange(0, CurrentPowerupSpawner.Num() - 1);
            ActivateSpawner(CurrentPowerupSpawner[NumberExtracted], TagsReferenceSettings->SpawnActionName);
        }
    }
}

void UWorldSubsystem_GameManager::UpdateMeleeEnemiesManager()
{
    if (ensureAlways(GameSubsystemSettings))
    {
        TArray<TSoftObjectPtr<ASpawner>> CurrentMeleeSpawner = PDA_GameSubsystemSetting->MeleeSpawners;

        for (int i = CurrentMeleeSpawner.Num() - 1; i >= 0; i--)
        {
            ASpawner* CurrentSpawner = CurrentMeleeSpawner[i].Get();
            if (!CurrentSpawner || !CurrentSpawner->CanSpawn())
            {
                CurrentMeleeSpawner.RemoveAt(i);
            }
        }

        if (CurrentMeleeSpawner.Num() > 0)
        {
            int NumberExtracted = FMath::RandRange(0, CurrentMeleeSpawner.Num() - 1);
            ActivateSpawner(CurrentMeleeSpawner[NumberExtracted], TagsReferenceSettings->SpawnActionName);
        }
    }
}

void UWorldSubsystem_GameManager::UpdateCoinsManager()
{
    if (ensureAlways(GameSubsystemSettings))
    {
        TSoftObjectPtr<ASpawner> CurrentCoinsSpawner = PDA_GameSubsystemSetting->CoinSpawner;
        ActivateSpawner(CurrentCoinsSpawner, TagsReferenceSettings->SpawnActionName);
    }
}

void UWorldSubsystem_GameManager::PrintSpawners(float DeltaTime)
{
    // Print all the spawner
    int CurrentFreeSpawners = 0;

    for (TSoftObjectPtr<ASpawner> SpawnerSoft : PDA_GameSubsystemSetting->RangeSpawners)
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

#pragma region Events

void UWorldSubsystem_GameManager::OnAllPlayersReady(AGameModeBase* CurrentGameMode)
{
    bActivateTick = true;
}

#pragma endregion

#pragma region AsynLoad

void UWorldSubsystem_GameManager::AsyncLoadData()
{
    if (ensureAlways(GameSubsystemSettings))
    {
        if (UAssetManager* Manager = UAssetManager::GetIfValid())
        {
            TArray<FName> Bundles;
            FPrimaryAssetId AssetId = GameSubsystemSettings->PA_GameSubsystemSetting;
            FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &UWorldSubsystem_GameManager::OnDataLoaded, AssetId);

            Manager->LoadPrimaryAsset(AssetId, Bundles, Delegate);
        }
    }
}

void UWorldSubsystem_GameManager::OnDataLoaded(FPrimaryAssetId AssetIdLoaded)
{
    UAssetManager* Manager = UAssetManager::GetIfValid();
    if (Manager)
    {
        PDA_GameSubsystemSetting = Cast<UPDA_GameSubsystem>(Manager->GetPrimaryAssetObject(AssetIdLoaded));
    }
}

#pragma endregion