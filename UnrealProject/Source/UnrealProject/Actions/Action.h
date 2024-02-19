// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "Action.generated.h"

class UActionComponent;

UCLASS()
class UNREALPROJECT_API UAction : public UObject
{
	GENERATED_BODY()


public:

	void Initialize(UActionComponent* NewActionComp);

	virtual bool CanStart();

	virtual void StartAction(AActor* Instigator);

	virtual void StopAction(AActor* Instigator);

#pragma region GetSet

public:

	UFUNCTION()
	FORCEINLINE bool GetIsRunning() const { return bIsRunning; }

	UFUNCTION()
	FORCEINLINE bool GetAutoPlay() const { return  bAutoPlay; }

	UFUNCTION()
	FORCEINLINE FGameplayTag GetActionName() const { return ActionName; }

#pragma endregion

#pragma region Variables

protected:

	UPROPERTY()
	bool bIsRunning = false;

	UPROPERTY()
	bool bAutoPlay = false;

	//Name of the action
	UPROPERTY()
	FGameplayTag ActionName;

	UPROPERTY()
	TObjectPtr<UActionComponent> ActionComponentOwner;

#pragma endregion

};
