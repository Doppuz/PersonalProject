// Fill out your copyright notice in the Description page of Project Settings.


#include "SquaredProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ASquaredProjectile::ASquaredProjectile()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
}

// Called when the game starts or when spawned
void ASquaredProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}