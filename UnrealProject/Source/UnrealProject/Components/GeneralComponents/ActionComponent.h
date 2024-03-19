// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "ActionComponent.generated.h"

class UAction;
class USAGameInstance;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJECT_API UActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActionComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, Category = "Action")
	void AddAction(AActor* Instigator, TSoftClassPtr<UAction> SoftActionClass);

	UFUNCTION(BlueprintCallable, Category = "Action")
	void RemoveAction(AActor* Instigator, UAction* ActionToRemove);

	UFUNCTION(BlueprintCallable, Category = "Action")
	void StartActionByName(AActor* Instigator, FGameplayTag ActionName);

	UFUNCTION(BlueprintCallable, Category = "Action")
	void StopActionByName(AActor* Instigator, FGameplayTag ActionName);

	UAction* GetAction(TSoftClassPtr<UAction> ActionSoftClass);

	bool ContainsActiveGameplayTags(FGameplayTagContainer InTags);

	void AddActiveTags(FGameplayTagContainer InTags);

	void RemoveActiveTags(FGameplayTagContainer InTags);

#pragma region Events

protected:

	UFUNCTION()
	void OnAllPlayersReady(AGameModeBase* CurrentGameMode);

#pragma endregion

#pragma region Server

public:

	UFUNCTION(Server, Reliable)
	void ServerStartAction(AActor* Instigator, FGameplayTag ActionName);

	UFUNCTION(Server, Reliable)
	void ServerStopAction(AActor* Instigator, FGameplayTag ActionName);

#pragma endregion

protected:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	virtual bool ContainsAction(TSoftClassPtr<UAction> SoftActionClass);

	UFUNCTION(CallInEditor, Category = "Debug")
	void PrintSingleDebugActions();

protected:

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Tags")
	FGameplayTagContainer ActiveGameplayTags;

	//List of actions not visible outside
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Actions")
	TArray<TObjectPtr<UAction>> CurrentActions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actions")
	TArray<TSoftClassPtr<UAction>> DefaultActions;

	UPROPERTY()
	USAGameInstance* GI;

	UPROPERTY()
	UWorldSubsystem_GlobalEvents* WS_GlobalEvents;

	UPROPERTY()
	bool DebugPrintSingleActions = false;

};
