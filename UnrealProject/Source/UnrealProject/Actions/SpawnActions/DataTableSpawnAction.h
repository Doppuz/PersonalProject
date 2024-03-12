// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Action.h"
#include "../../Enums/Enums_General.h"
#include "DataTableSpawnAction.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable)
class UNREALPROJECT_API UDataTableSpawnAction : public UAction
{
	GENERATED_BODY()
	
public:

	virtual void StartAction_Implementation(AActor* Instigator) override;

protected:

	virtual bool DataTableFilterCondition(const FPrimaryDataAssetRow* InTableRow);

	void DataTableFilterRows(TArray<FPrimaryDataAssetRow*>& OutTableRows);

	FPrimaryDataAssetRow* GetSelectedRow();

	void AsyncLoadPrimaryAsset(FPrimaryDataAssetRow* PrimaryDataAssetRow);

	UFUNCTION()
	virtual void OnRowLoaded(FPrimaryAssetId LoadedId);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
	TObjectPtr<class UDataTable> SpawnDataTable;

};
