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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
	bool CanStart();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
	void StopAction(AActor* Instigator);

protected:

	virtual bool IsSupportedForNetworking() const override
	{
		return true;
	}

	UFUNCTION()
	void OnRep_RepActionData();

	void OnCooldownExpire();

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Information")
	bool bAutoPlay = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Base Information")
	bool bAutoRemove = false;

#pragma region Cooldown

	UPROPERTY(replicated)
	bool bIsInCooldown = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Base Information | Cooldown")
	float CooldownAmount = 0.f;

	UPROPERTY()
	FTimerHandle CooldownTimerHandle;

#pragma endregion

	//Name of the action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Information")
	FGameplayTag ActionName;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer GrantsTags;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer BlockedTags;

	UPROPERTY(Replicated, BlueprintReadOnly)
	TObjectPtr<UActionComponent> ActionComponentOwner;

	UPROPERTY()
	class USAGameInstance* GI = nullptr;

	UPROPERTY()
	class UWorldSubsystem_GlobalEvents* WS_GlobalEvents;

};
