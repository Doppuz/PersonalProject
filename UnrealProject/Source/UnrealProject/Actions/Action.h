// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "Action.generated.h"

class UActionComponent;

UCLASS(Blueprintable)
class UNREALPROJECT_API UAction : public UObject
{
	GENERATED_BODY()


public:

	virtual void Initialize(UActionComponent* NewActionComp);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	bool CanStart();

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StopAction(AActor* Instigator);

#pragma region GetSet

public:

	UFUNCTION()
	FORCEINLINE bool GetIsRunning() const { return bIsRunning; }

	UFUNCTION()
	FORCEINLINE bool GetAutoPlay() const { return  bAutoPlay; }

	UFUNCTION()
	FORCEINLINE FGameplayTag GetActionName() const { return ActionName; }

#pragma endregion

protected:

	UPROPERTY()
	bool bIsRunning = false;

	UPROPERTY()
	bool bAutoPlay = false;

	//Name of the action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Information")
	FGameplayTag ActionName;

	UPROPERTY()
	TObjectPtr<UActionComponent> ActionComponentOwner;

	UPROPERTY()
	class USAGameInstance* GI = nullptr;

};
