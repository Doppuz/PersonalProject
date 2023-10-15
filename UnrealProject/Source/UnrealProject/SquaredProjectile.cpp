// Fill out your copyright notice in the Description page of Project Settings.


#include "SquaredProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interfaces/MovementInterface.h"
#include "Components/BoxComponent.h"

// Sets default values
ASquaredProjectile::ASquaredProjectile()
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
void ASquaredProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	if (ProjectileOwner)
	{
		IMovementInterface* ProjectileOwnerMovementInterface = Cast<IMovementInterface>(ProjectileOwner);

		if (ProjectileOwnerMovementInterface)
		{
			FVector ProjectileOwnerSpeed = ProjectileOwnerMovementInterface->GetCurrentMovementSpeed();

			ProjectileMovementComponent->Velocity += ProjectileOwnerSpeed;
		}
	}

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASquaredProjectile::OnComponentBeginOverlap);
}

void ASquaredProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	BoxComponent->OnComponentBeginOverlap.RemoveDynamic(this, &ASquaredProjectile::OnComponentBeginOverlap);
}

void ASquaredProjectile::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != GetOwner())
	{
		Destroy();
	}
}

void ASquaredProjectile::SetProjectileOwner(AActor* InActor)
{
	if (InActor)
	{
		ProjectileOwner = InActor;
	}
}
