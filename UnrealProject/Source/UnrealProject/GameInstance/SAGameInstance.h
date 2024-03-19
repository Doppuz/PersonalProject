// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "SAGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API USAGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UFUNCTION()
	FORCEINLINE TSoftClassPtr<AActor> GetDebugActionComponentClass() { return DebugActionComponentClass; }

	UFUNCTION()
	FORCEINLINE TSoftClassPtr<AActor> GetDebugStatManagerClass() { return DebugStatManagerClass; }

public:

	FStreamableManager StreamableManager;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	TSoftClassPtr<AActor> DebugActionComponentClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	TSoftClassPtr<AActor> DebugStatManagerClass;
};
