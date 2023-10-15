// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "../Interfaces/ShootInterface.h"
#include "../Interfaces/PatrolInterface.h"
#include "ShooterEnemy.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API AShooterEnemy : public ABaseEnemy, public IShootInterface, public IPatrolInterface
{
	GENERATED_BODY()
	
public:

	AShooterEnemy();

#pragma region PatrolInterface

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "PatrolRoute")
	class APatrolRoute* PatrolRoute;

	virtual class APatrolRoute* GetPatrolRoute();

#pragma endregion

#pragma region ShooterInterface

	virtual FVector GetShootStartingLocation();

	virtual class UShooterComponent* GetShooterComponent();

#pragma endregion

protected:

#pragma region components

	UPROPERTY(EditAnywhere, Category = "Components")
	class UShooterComponent* ShooterComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* ShootPoint;

#pragma endregion

};
