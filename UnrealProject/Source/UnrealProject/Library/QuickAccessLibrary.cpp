// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickAccessLibrary.h"
#include "../GameInstance/SAGameInstance.h"
#include "../Characters/MainCharacter.h"
#include "Engine/AssetManager.h"
#include "../Components/GeneralComponents/ActionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../UnrealProjectGameModeBase.h"
#include "../GameState/SAGameStateBase.h"
#include "../PlayerState/SAPlayerState.h"
#include "../Components/GeneralComponents/StatsManager.h"
#include "../Enums/Enums_Stat.h"

USAGameInstance* UQuickAccessLibrary::GetGameInstance(UObject* WorldContextObject)
{
	if (!WorldContextObject)
	{
		return nullptr;
	}

	UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);

	return Cast<USAGameInstance>(World->GetGameInstance());
}

AMainCharacter* UQuickAccessLibrary::GetPlayer(UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);

	if (ensure(World))
	{
		APlayerController* PC = World->GetFirstPlayerController();
		if (PC)
		{
			AMainCharacter* curChar = Cast<AMainCharacter>(PC->GetPawn());
			return curChar;
		}
	}

	return nullptr;
}

bool UQuickAccessLibrary::SoftClassIsChildOf(const TSoftClassPtr<UObject>& SoftClass, const TSubclassOf<UObject>& Class)
{
	if (SoftClass.IsNull() || Class == nullptr)
	{
		// Class is invalid, do nothing
		return false;
	}
	else if (const UClass* LoadedClass = SoftClass.Get())
	{
		// Class is already loaded, use the fast path
		return LoadedClass->IsChildOf(Class);
	}
	else
	{
		// Use Asset Registry for Unloaded Classes
		// Caution: This may be slow if TempCaching is disabled.
		FAssetData AssetData;
		if (UAssetManager::Get().GetAssetDataForPath(SoftClass.ToSoftObjectPath(), AssetData))
		{
			if (AssetData.AssetClassPath == FTopLevelAssetPath(Class))
			{
				return true;
			}
			else
			{
				// Unfortunately the temp class hierarchy data is private, so we can't walk it manually.
				TArray<FTopLevelAssetPath> AncestorClasses;
				IAssetRegistry::Get()->GetAncestorClassNames(AssetData.AssetClassPath, AncestorClasses);

				return AncestorClasses.Contains(FTopLevelAssetPath(Class));
			}
		}

		return false;
	}
}

bool UQuickAccessLibrary::ClassIsChildOfSoft(const TSoftClassPtr<UObject>& SoftClass, const TSubclassOf<UObject>& Class)
{
	if (SoftClass.IsNull() || Class == nullptr)
	{
		// Class is invalid, do nothing
		return false;
	}
	else if (const UClass* LoadedClass = SoftClass.Get())
	{
		// Class is already loaded, use the fast path
		return Class->IsChildOf(LoadedClass);
	}
	else
	{
		// Use Asset Registry for Unloaded Classes
		// Caution: This may be slow if TempCaching is disabled.
		FAssetData AssetData;
		if (UAssetManager::Get().GetAssetDataForPath(SoftClass.ToSoftObjectPath(), AssetData))
		{
			if (AssetData.AssetClassPath == FTopLevelAssetPath(Class))
			{
				return true;
			}
			else
			{
				// Unfortunately the temp class hierarchy data is private, so we can't walk it manually.
				TArray<FTopLevelAssetPath> AncestorClasses;
				IAssetRegistry::Get()->GetAncestorClassNames(FTopLevelAssetPath(Class), AncestorClasses);

				return AncestorClasses.Contains(FTopLevelAssetPath(AssetData.AssetClassPath));
			}
		}

		return false;
	}
}

bool UQuickAccessLibrary::StartAction(UObject* WorldContextObject, AActor* Instigator, const AActor* CurrentActor, const FGameplayTag ActionName)
{
	if (ensureAlways(CurrentActor))
	{
		UActionComponent* CurrentActionComponent = Cast<UActionComponent>(CurrentActor->FindComponentByClass(UActionComponent::StaticClass()));

		if (CurrentActionComponent)
		{
			CurrentActionComponent->StartActionByName(Instigator, ActionName);
			return true;
		}
	}

	return false;
}

bool UQuickAccessLibrary::AddAction(UObject* WorldContextObject, AActor* Instigator, const AActor* CurrentActor, const TSoftClassPtr<UAction> NewAction)
{
	if (ensureAlways(CurrentActor) && ensureAlways(CurrentActor->HasAuthority()))
	{
		UActionComponent* CurrentActionComponent = Cast<UActionComponent>(CurrentActor->FindComponentByClass(UActionComponent::StaticClass()));

		if (CurrentActionComponent)
		{
			CurrentActionComponent->AddAction_Soft(Instigator, NewAction);
			return true;
		}
	}

	return false;
}

bool UQuickAccessLibrary::HasGameplayTags(UObject* WorldContextObject, AActor* InActor, FGameplayTagContainer GameplayTag)
{
	if (ensureAlways(InActor))
	{
		UActionComponent* CurrentActionComponent = Cast<UActionComponent>(InActor->FindComponentByClass(UActionComponent::StaticClass()));

		if (CurrentActionComponent)
		{
			return CurrentActionComponent->ContainsActiveGameplayTags(GameplayTag);
		}
	}

	return false;
}

ETeamAttitude::Type UQuickAccessLibrary::GetTeamAttitude(UObject* WorldContextObject, AActor* FirstActor, const AActor* SecondActor)
{
	APawn* FirstActorPawn = Cast<APawn>(FirstActor);
	if (ensureAlways(FirstActorPawn) && ensureAlways(SecondActor))
	{
		IGenericTeamAgentInterface* FirstActorTeamInterface = Cast<IGenericTeamAgentInterface>(FirstActorPawn->GetController());

		if (FirstActorTeamInterface)
		{
			return FirstActorTeamInterface->GetTeamAttitudeTowards(*SecondActor);
		}
	}

	return ETeamAttitude::Neutral;
}

AUnrealProjectGameModeBase* UQuickAccessLibrary::GetCurrentGameMode(UObject* WorldContextObject)
{
	return Cast<AUnrealProjectGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
}

bool UQuickAccessLibrary::GetAreAllPlayersReady(UObject* WorldContextObject)
{
	AUnrealProjectGameModeBase* UnrealProjectGameModeBase = UQuickAccessLibrary::GetCurrentGameMode(WorldContextObject);

	if (ensureAlways(UnrealProjectGameModeBase))
	{
		return UnrealProjectGameModeBase->GetAreAllPlayersReady();
	}

	return false;
}

ASAGameStateBase* UQuickAccessLibrary::GetGameState(UObject* WorldContextObject)
{
	if (!WorldContextObject)
	{
		return nullptr;
	}

	if (UWorld* World = WorldContextObject->GetWorld())
	{
		return Cast<ASAGameStateBase>(World->GetGameState());
	}

	return nullptr;
}

void UQuickAccessLibrary::AddScoreToAllPlayers(AActor* Instigator, float ScoreToAdd)
{
	if (ensureAlways(Instigator) && ensureAlways(Instigator->HasAuthority()))
	{
		AGameStateBase* GS = GetGameState(Instigator);

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
}

void UQuickAccessLibrary::ApplyDamageToActor(AActor* FromActor, AActor* ToActor, float DamageAmount)
{
	if (FromActor && ToActor && FromActor->HasAuthority())
	{
		UStatsManager* OtherActorStatManager = Cast<UStatsManager>(ToActor->FindComponentByClass(UStatsManager::StaticClass()));

		if (OtherActorStatManager)
		{
			ETeamAttitude::Type TeamAttitudeType = QL::GetTeamAttitude(FromActor, FromActor, ToActor);

			if (TeamAttitudeType == ETeamAttitude::Hostile || TeamAttitudeType == ETeamAttitude::Neutral)
			{
				OtherActorStatManager->ChangeStat(FromActor, EStatCategory::HEALTH, -DamageAmount);
			}
		}
	}
}
