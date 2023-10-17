// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EQS_Context_Attacktarget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UEQS_Context_Attacktarget : public UEnvQueryContext
{
	GENERATED_BODY()
	
protected:

	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

};
