// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../Interfaces/MovementInterface.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "../Components/GeneralComponents/StatsManager.h"
#include "../Enums/Enums_Stat.h"
#include "GenericTeamAgentInterface.h"
#include "../Library/QuickAccessLibrary.h"
#include "Components/CapsuleComponent.h"
#include "../Settings/TagsReferenceSettings.h"
#include "../Characters/BaseCharacter.h"

// Sets default values
ABasicProjectile::ABasicProjectile()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	MeshComponent->SetCollisionProfileName("NoCollision");

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(MeshComponent);
	SphereComponent->SetCollisionProfileName(TEXT("ProjectilePreset"));

	ProjectileParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ProjectileParticleComponent"));
	ProjectileParticleComponent->SetupAttachment(SphereComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	SetReplicates(true);
}

// Called when the game starts or when spawned
void ABasicProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABasicProjectile::OnComponentBeginOverlap);

	TagsReferenceSettings = GetDefault<UTagsReferenceSettings>();

	if (ensureAlways(GetWorld()))
	{
		GetWorld()->GetTimerManager().SetTimer(DestroyTimer, this, &ABasicProjectile::DestroyProjectile, DestroyTimerDuration, false);
	}
}

void ABasicProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(DestroyTimer);
	SphereComponent->OnComponentBeginOverlap.RemoveDynamic(this, &ABasicProjectile::OnComponentBeginOverlap);
}

void ABasicProjectile::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != GetOwner() && OtherActor != this && !OtherActor->IsA(ABasicProjectile::StaticClass()))
	{
		if (HasAuthority() && TagsReferenceSettings && !QL::HasGameplayTags(this, OtherActor, FGameplayTagContainer(TagsReferenceSettings->ShieldTag)))
		{
			QL::ApplyDamageToActor(GetInstigator(), OtherActor, Damage);
			QL::StartAction(GetWorld(), GetInstigator(), OtherActor, TagsReferenceSettings->HitReactionActionName);

			Destroy();
		}
	}
}

void ABasicProjectile::DestroyProjectile()
{
	Destroy();
}
