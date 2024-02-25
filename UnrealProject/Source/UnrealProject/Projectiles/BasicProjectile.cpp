// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../Interfaces/MovementInterface.h"
#include "Components/BoxComponent.h"

// Sets default values
ABasicProjectile::ABasicProjectile()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	MeshComponent->SetCollisionProfileName("NoCollision");

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(MeshComponent);

	BoxComponent->SetCollisionProfileName("OverlapAll");

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
}

// Called when the game starts or when spawned
void ABasicProjectile::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABasicProjectile::OnComponentBeginOverlap);
}

void ABasicProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	BoxComponent->OnComponentBeginOverlap.RemoveDynamic(this, &ABasicProjectile::OnComponentBeginOverlap);
}

void ABasicProjectile::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != GetOwner())
	{
		Destroy();
	}
}