// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "ActionComponent.generated.h"

class UAction;
class UShooterGameInstance;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJECT_API UActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void AddAction(AActor* Instigator, TSoftClassPtr<UAction> SoftActionClass);

	void RemoveAction(AActor* Instigator, UAction* ActionToRemove);

	void StartActionByName(AActor* Instigator, FGameplayTag ActionName);

	void StopActionByName(AActor* Instigator, FGameplayTag ActionName);

	UAction* GetAction(TSoftClassPtr<UAction> ActionSoftClass);

#pragma region Variables

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer ActiveGameplayTags;

	//List of actions not visible outside
	UPROPERTY()
	TArray<TObjectPtr<UAction>> CurrentActions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actions")
	TArray<TObjectPtr<UAction>> DefaultActions;

	UPROPERTY()
	TSoftObjectPtr<UShooterGameInstance> GI;

#pragma endregion

};
