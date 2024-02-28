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

	void AddAction(AActor* Instigator, TSoftClassPtr<UAction> SoftActionClass);

	void RemoveAction(AActor* Instigator, UAction* ActionToRemove);

	void StartActionByName(AActor* Instigator, FGameplayTag ActionName);

	void StopActionByName(AActor* Instigator, FGameplayTag ActionName);

	UAction* GetAction(TSoftClassPtr<UAction> ActionSoftClass);

	bool ContainsActiveGameplayTags(FGameplayTagContainer InTags);

	void AddActiveTags(FGameplayTagContainer InTags);

	void RemoveActiveTags(FGameplayTagContainer InTags);

#pragma region Server

	UFUNCTION(Server, Reliable)
	void ServerStartAction(AActor* Instigator, FGameplayTag ActionName);

	UFUNCTION(Server, Reliable)
	void ServerStopAction(AActor* Instigator, FGameplayTag ActionName);

#pragma endregion

protected:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

protected:

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Tags")
	FGameplayTagContainer ActiveGameplayTags;

	//List of actions not visible outside
	UPROPERTY(Replicated)
	TArray<TObjectPtr<UAction>> CurrentActions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actions")
	TArray<TSoftClassPtr<UAction>> DefaultActions;

	UPROPERTY()
	TObjectPtr<USAGameInstance> GI;


};
