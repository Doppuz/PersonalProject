// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enums_Stat.generated.h"

UENUM(BlueprintType)
enum class EStatCategory : uint8
{
	HEALTH,
	MAX UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FStatCategoryValue
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	EStatCategory StatCategory = EStatCategory::MAX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float Value = 0.f;

};

USTRUCT(BlueprintType)
struct FStatValue
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float CurrentValue = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MinValue = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MaxValue = 100.f;

};

USTRUCT(BlueprintType)
struct FStat_Broadcast
{
	GENERATED_BODY()

public:

	FStat_Broadcast() {};

	FStat_Broadcast(AActor* InOwner, FStatValue InStatValue, float InOldValue, EStatCategory InStatCategory) :
		Owner(InOwner), StatValue(InStatValue), OldValue(InOldValue), StatCategory(InStatCategory) {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	AActor* Owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	FStatValue StatValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float OldValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	EStatCategory StatCategory = EStatCategory::MAX;

};

UCLASS()
class UNREALPROJECT_API UEnums_Stat : public UObject
{
	GENERATED_BODY()
	
};
