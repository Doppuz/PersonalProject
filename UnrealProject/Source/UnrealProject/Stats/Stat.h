// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Enums/Enums_Stat.h"
#include "Stat.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UNREALPROJECT_API UStat : public UObject
{
	GENERATED_BODY()
	
public:

	virtual void Initialize();

	FStat_Broadcast ChangeStat(AActor* Instigator, float Value);

protected:

	UFUNCTION(BlueprintNativeEvent, Category = "Stat")
	void OnStatReachesMinValue(AActor* Instigator);

#pragma region GetSet

public:

	UFUNCTION()
	FORCEINLINE EStatCategory GetStatCategory() { return StatCategory; }

	UFUNCTION()
	FORCEINLINE FStatValue GetStatValue() { return StatValue; }

#pragma endregion

	virtual bool IsSupportedForNetworking() const override
	{
		return true;
	}

protected:

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (FullyExpand = true))
	FStatValue StatValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	EStatCategory StatCategory = EStatCategory::MAX;

	UPROPERTY()
	class UStatsManager* StatsManagerRef;

};
