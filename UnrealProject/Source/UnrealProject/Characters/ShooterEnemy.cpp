// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterEnemy.h"
#include "../Components/GeneralComponents/ShooterComponent.h"

AShooterEnemy::AShooterEnemy()
{
	ShootPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ShootPoint"));
	ShootPoint->SetupAttachment(RootComponent);

	ShooterComponent = CreateDefaultSubobject<UShooterComponent>(TEXT("ShooterComponent"));
}

#pragma region PatrolInterface

APatrolRoute* AShooterEnemy::GetPatrolRoute()
{
	return PatrolRoute;
}

#pragma endregion

#pragma region ShootInterface

FVector AShooterEnemy::GetShootStartingLocation()
{
	return ShootPoint->GetComponentLocation();
}

UShooterComponent* AShooterEnemy::GetShooterComponent()
{
	return ShooterComponent;
}

#pragma endregion