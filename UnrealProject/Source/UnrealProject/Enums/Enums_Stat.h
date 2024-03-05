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

UCLASS()
class UNREALPROJECT_API UEnums_Stat : public UObject
{
	GENERATED_BODY()
	
};
