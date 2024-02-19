// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QuickAccessLibrary.generated.h"

#define QL UQuickAccessLibrary

UCLASS()
class UNREALPROJECT_API UQuickAccessLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure, Category = "QuickLibrary", meta = (WorldContext = "WorldContextObject"))
	static class UShooterGameInstance* GetGameInstance(UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "QuickLibrary", meta = (WorldContext = "WorldContextObject"))
	static class AMainCharacter* GetPlayer(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "QuickLibrary")
	static bool SoftClassIsChildOf(const TSoftClassPtr<UObject>& SoftClass, const TSubclassOf<UObject>& Class);

	UFUNCTION(BlueprintCallable, Category = "QuickLibrary")
	static bool ClassIsChildOfSoft(const TSoftClassPtr<UObject>& SoftClass, const TSubclassOf<UObject>& Class);

};