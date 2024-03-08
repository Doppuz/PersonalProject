// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interfaces/MovementInterface.h"
#include "BaseCharacter.generated.h"

class UActionComponent;
class UStatsManager;

UCLASS()
class UNREALPROJECT_API ABaseCharacter : public ACharacter, public IMovementInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

#pragma region MovementInterface

	virtual FVector GetCurrentMovementSpeed();

	virtual void SetCurrentMovementSpeed(float Invalue);

	virtual class UMovementManager* GetMovementManager();

#pragma endregion

#pragma region GetSet

	UFUNCTION()
	FORCEINLINE UActionComponent* GetActionComponent() { return ActionComponent; }

	UFUNCTION()
	FORCEINLINE UStatsManager* GetStatsManager() { return StatsManager; }

	UFUNCTION()
	FORCEINLINE UAnimInstance* GetAnimInstance() { return GetMesh() ? GetMesh()->GetAnimInstance() : nullptr; }

	UFUNCTION()
	FORCEINLINE UMaterialInstanceDynamic* GetMaterialInstanceDynamic() { return MaterialInstanceDynamic; }

#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> MaterialInstanceDynamic = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UActionComponent> ActionComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStatsManager> StatsManager = nullptr;
};
