// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickAccessLibrary.h"
#include "../GameInstance/SAGameInstance.h"
#include "../Characters/MainCharacter.h"
#include "Engine/AssetManager.h"
#include "../Components/GeneralComponents/ActionComponent.h"

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
