// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterEnemy.h"

AShooterEnemy::AShooterEnemy()
{

}

#pragma region PatrolInterface

APatrolRoute* AShooterEnemy::GetPatrolRoute()
{
	return PatrolRoute;
}

#pragma endregion
