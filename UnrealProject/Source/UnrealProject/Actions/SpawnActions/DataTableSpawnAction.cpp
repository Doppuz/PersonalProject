// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTableSpawnAction.h"
#include "Engine/DataTable.h"	
#include "Engine/AssetManager.h"

void UDataTableSpawnAction::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	FPrimaryDataAssetRow* SelectedRow = GetSelectedRow();

	if (SelectedRow)
	{
		AsyncLoadPrimaryAsset(SelectedRow);
	}
}

bool UDataTableSpawnAction::DataTableFilterCondition(const FPrimaryDataAssetRow* InTableRow)
{
	return true;
}

void UDataTableSpawnAction::DataTableFilterRows(TArray<FPrimaryDataAssetRow*>& OutTableRows)
{
	for (int i = OutTableRows.Num() - 1; i > 0; i--)
	{
		if (!DataTableFilterCondition(OutTableRows[i]))
		{
			OutTableRows.RemoveAt(i);
		}
	}
}

FPrimaryDataAssetRow* UDataTableSpawnAction::GetSelectedRow()
{
	TArray<FPrimaryDataAssetRow*> Rows;
	SpawnDataTable->GetAllRows("", Rows);

	DataTableFilterRows(Rows);

	if (Rows.Num() > 0)
	{
		int RandomRow = FMath::RandRange(0, Rows.Num() - 1);

		return Rows[RandomRow];
	}

	return nullptr;
}

void UDataTableSpawnAction::AsyncLoadPrimaryAsset(FPrimaryDataAssetRow* PrimaryDataAssetRow)
{
	if (UAssetManager* Manager = UAssetManager::GetIfValid())
	{
		TArray<FName> Bundles;
		FPrimaryAssetId AssetId = PrimaryDataAssetRow->PrimaryAssetId;
		FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &UDataTableSpawnAction::OnRowLoaded, AssetId);

		Manager->LoadPrimaryAsset(AssetId, Bundles, Delegate);
	}
}

void UDataTableSpawnAction::OnRowLoaded(FPrimaryAssetId LoadedId)
{
	//Override children
}
