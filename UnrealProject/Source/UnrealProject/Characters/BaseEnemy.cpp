// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "../Components/GeneralComponents/MovementManager.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementManager = CreateDefaultSubobject<UMovementManager>(TEXT("MovementManager"));
}

#pragma region MovementInterface

UMovementManager* ABaseEnemy::GetMovementManager()
{
	return MovementManager;
}

#pragma endregion

#pragma region AttackDefenseInterface

float ABaseEnemy::GetAttackRange()
{
	return AttackRange;
}

float ABaseEnemy::GetDefenseRange()
{
	return DefenseRange;
}

#pragma endregion


// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}