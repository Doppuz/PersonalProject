// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldSubsystem_GameManager.h"
#include "../../Settings/GameSubsystemSettings.h"
#include "../../Library/QuickAccessLibrary.h"
#include "../../Spawners/Spawner.h"
#include "Engine/AssetManager.h"
#include "../../Subsystem/WorldSubsystem/WorldSubsystem_GlobalEvents.h"
#include "../../GameState/SAGameStateBase.h"
#include "../../PlayerState/SAPlayerState.h"
#include "../../UnrealProjectGameModeBase.h"

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

    if (ensure(WS_GlobalEvents))
    {
        WS_GlobalEvents->OnAllPlayersReady.AddDynamic(this, &UWorldSubsystem_GameManager::OnAllPlayersReady);
    }
}

void UWorldSubsystem_GameManager::Tick(float DeltaTime)
{
    if (bActivateTick)
    {
        CurrentTick += DeltaTime;
        CurrentPowerUpTick += DeltaTime;
        CurrentScoreTick += DeltaTime;

        CheckFrequency = FMath::RandRange(3.f, 7.f);

        if (CurrentTick >= CheckFrequency)
        {
            UpdateManager();

            CurrentTick = 0.f;
        }

        if (CurrentPowerUpTick >= PowerupCheckFrequency)
        {
            UpdatePowerUpManager();

            CurrentPowerUpTick = 0.f;
        }

        if (CurrentScoreTick >= ScoreCheckFrequency)
        {
            IncreaseScore(ScoreCheckFrequency);

            CurrentScoreTick = 0.f;
        }

        if (DebugPrintSpawners > 0 && GEngine && GameSubsystemSettings)
        {
            PrintSpawners(DeltaTime);
        }
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

void UWorldSubsystem_GameManager::UpdatePowerUpManager()
{
    if (ensureAlways(GameSubsystemSettings))
    {
        TArray<TSoftObjectPtr<ASpawner>> CurrentPowerupSpawner = GameSubsystemSettings->PowerupSpawners;

        if (CurrentPowerupSpawner.Num() > 0)
        {
            int NumberExtracted = FMath::RandRange(0, CurrentPowerupSpawner.Num() - 1);
            ActivateSpawner(CurrentPowerupSpawner[NumberExtracted], GameSubsystemSettings->SpawnActionName);
        }
    }
}

void UWorldSubsystem_GameManager::IncreaseScore(float ScoreToAdd)
{
    AGameStateBase* GS = QL::GetGameState(this);

    if (ensureAlways(GS))
    {
        TArray<TObjectPtr<APlayerState>> PlayerStates = GS->PlayerArray;

        for (int i = 0; i < PlayerStates.Num(); i++)
        {
            ASAPlayerState* CurrentPS = Cast<ASAPlayerState>(PlayerStates[i]);

            if (CurrentPS)
            {
                CurrentPS->UpdatePlayerScore(ScoreToAdd);
            }
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

#pragma region Events

void UWorldSubsystem_GameManager::OnAllPlayersReady(AGameModeBase* CurrentGameMode)
{
    bActivateTick = true;
}

#pragma endregion