// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/StreamableManager.h"
#include "Perception/AIPerceptionTypes.h"
#include "QuickAccessLibrary.generated.h"

#define QL UQuickAccessLibrary

UCLASS()
class UNREALPROJECT_API UQuickAccessLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure, Category = "QuickLibrary", meta = (WorldContext = "WorldContextObject"))
	static class USAGameInstance* GetGameInstance(UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "QuickLibrary", meta = (WorldContext = "WorldContextObject"))
	static class AMainCharacter* GetPlayer(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "QuickLibrary")
	static bool SoftClassIsChildOf(const TSoftClassPtr<UObject>& SoftClass, const TSubclassOf<UObject>& Class);

	UFUNCTION(BlueprintCallable, Category = "QuickLibrary")
	static bool ClassIsChildOfSoft(const TSoftClassPtr<UObject>& SoftClass, const TSubclassOf<UObject>& Class);

	//StartAction from the actor action component
	UFUNCTION(BlueprintCallable, Category = "QuickLibrary")
	static bool StartAction(UObject* WorldContextObject, AActor* Instigator, const AActor* CurrentActor, const FGameplayTag ActionName);

	//Add action from the actor action component
	UFUNCTION(BlueprintCallable, Category = "QuickLibrary")
	static bool AddAction(UObject* WorldContextObject, AActor* Instigator, const AActor* CurrentActor, const TSoftClassPtr<UAction> NewAction);

	UFUNCTION(BlueprintCallable, Category = "QuickLibrary")
	static ETeamAttitude::Type GetTeamAttitude(UObject* WorldContextObject, AActor* FirstActor, const AActor* SecondActor);

	UFUNCTION(BlueprintCallable, Category = "QuickLibrary")
	static class AUnrealProjectGameModeBase* GetCurrentGameMode(UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "QuickLibrary", meta = (WorldContext = "WorldContextObject"))
	static bool GetAreAllPlayersReady(UObject* WorldContextObject);
};