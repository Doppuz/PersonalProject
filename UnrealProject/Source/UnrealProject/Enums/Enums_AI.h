// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Enums_AI.generated.h"

class UPDA_EnemyAI;

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	PASSIVE,
	ATTACKING,
	INVESTIGATING,
	MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EAISense : uint8
{
	SIGHT,
	HEARING,
	DAMAGE,
	MAX UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FEnemyRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Asset")
	UPDA_EnemyAI* EnemyDataAsset;
};

UCLASS()
class UNREALPROJECT_API UEnums_AI : public UObject
{
	GENERATED_BODY()
	
};
