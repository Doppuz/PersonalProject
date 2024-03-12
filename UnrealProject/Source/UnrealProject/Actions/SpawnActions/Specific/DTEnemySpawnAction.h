// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../DataTableSpawnAction.h"
#include "DTEnemySpawnAction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UNREALPROJECT_API UDTEnemySpawnAction : public UDataTableSpawnAction
{
	GENERATED_BODY()
	
protected:

	virtual bool DataTableFilterCondition(const FPrimaryDataAssetRow* InTableRow);

	virtual void OnRowLoaded(FPrimaryAssetId LoadedId);

};
