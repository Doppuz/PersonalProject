// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AsyncLoadInterface.generated.h"

UINTERFACE(MinimalAPI)
class UAsyncLoadInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREALPROJECT_API IAsyncLoadInterface
{
	GENERATED_BODY()

public:

	virtual void AsyncLoadData();
	virtual void ResetData();
};
