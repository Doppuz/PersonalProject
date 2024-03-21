// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Enums_General.generated.h"

USTRUCT(BlueprintType)
struct FPrimaryDataAssetRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Asset")
	FPrimaryAssetId PrimaryAssetId;
};

UCLASS()
class UNREALPROJECT_API UEnums_General : public UObject
{
	GENERATED_BODY()
	
};
