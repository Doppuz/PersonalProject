// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "Action.generated.h"

USTRUCT()
struct FActionRepData
{
	GENERATED_BODY()

public:

	UPROPERTY()
	bool bIsRunning;

	UPROPERTY()
	TObjectPtr<AActor> Instigator;

	FActionRepData()
	{
		bIsRunning = false;
	}
};

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

protected:

	virtual bool IsSupportedForNetworking() const override
	{
		return true;
	}

	UFUNCTION()
	void OnRep_RepActionData();

#pragma region GetSet

public:

	UFUNCTION()
	FORCEINLINE bool GetIsRunning() const { return ActionRepData.bIsRunning; }

	UFUNCTION()
	FORCEINLINE bool GetAutoPlay() const { return  bAutoPlay; }

	UFUNCTION()
	FORCEINLINE FGameplayTag GetActionName() const { return ActionName; }

#pragma endregion

protected:

	UPROPERTY(ReplicatedUsing = "OnRep_RepActionData")
	struct FActionRepData ActionRepData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Information")
	bool bAutoPlay = false;

	//Name of the action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Information")
	FGameplayTag ActionName;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer GrantsTags;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer BlockedTags;

	UPROPERTY(Replicated)
	TObjectPtr<UActionComponent> ActionComponentOwner;

	UPROPERTY()
	class USAGameInstance* GI = nullptr;

	UPROPERTY()
	class UWorldSubsystem_GlobalEvents* WS_GlobalEvents;

};
