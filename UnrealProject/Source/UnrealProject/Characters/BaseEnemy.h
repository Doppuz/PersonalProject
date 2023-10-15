// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "../Enums/Enums_AI.h"
#include "BaseEnemy.generated.h"

UCLASS()
class UNREALPROJECT_API ABaseEnemy : public ABaseCharacter
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

};
