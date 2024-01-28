// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "../Enums/Enums_AI.h"
#include "../Interfaces/AttackDefenseInterface.h"
#include "BaseEnemy.generated.h"

UCLASS()
class UNREALPROJECT_API ABaseEnemy : public ABaseCharacter, public IAttackDefenseInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region MovementInterface

public:

	virtual class UMovementManager* GetMovementManager() override;

protected:

	UPROPERTY(EditAnywhere, Category = "Components")
	class UMovementManager* MovementManager;

#pragma endregion

#pragma region AttackDefenseInterface

public:
	
	UFUNCTION()
	virtual float GetAttackRange();

	UFUNCTION()
	virtual float GetDefenseRange();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AttackDefenseRange")
	float AttackRange = 150.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AttackDefenseRange")
	float DefenseRange = 350.f;

#pragma endregion

};
