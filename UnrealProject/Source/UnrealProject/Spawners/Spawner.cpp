// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Components/BillboardComponent.h"	
#include "Components/CapsuleComponent.h"
#include "../Components/GeneralComponents/ActionComponent.h"
#include "Components/ArrowComponent.h"
#include "../Subsystem/WorldSubsystem/WorldSubsystem_GlobalEvents.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = CapsuleComponent;

#if WITH_EDITORONLY_DATA

	EditorTexture = CreateDefaultSubobject<UBillboardComponent>(TEXT("EditorTexture"));
	EditorTexture->SetupAttachment(RootComponent);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(RootComponent);

#endif

	ActionComponent = CreateDefaultSubobject<UActionComponent>(TEXT("ActionComponent"));

	bReplicates = true;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	WS_GlobalEvents = GetWorld()->GetSubsystem<UWorldSubsystem_GlobalEvents>();

	if (HasAuthority())
	{
		if (ensureAlways(WS_GlobalEvents))
		{
			WS_GlobalEvents->OnActionSpawnActor.AddDynamic(this, &ASpawner::OnActionSpawnActor);
			WS_GlobalEvents->OnActionActorDead.AddDynamic(this, &ASpawner::OnActionActorDead);
		}
	}
}

void ASpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (HasAuthority())
	{
		if (ensureAlways(WS_GlobalEvents))
		{
			WS_GlobalEvents->OnActionSpawnActor.RemoveDynamic(this, &ASpawner::OnActionSpawnActor);
			WS_GlobalEvents->OnActionActorDead.RemoveDynamic(this, &ASpawner::OnActionActorDead);
		}
	}
}

bool ASpawner::CanSpawn()
{
	if (SpawnerType == ESpawnerType::SINGLE)
	{
		if(CurrentActorsSpawned.Num() > 0)
		{
			return false;
		}
	}

	return true;
}

void ASpawner::OnActionSpawnActor(UActionComponent* InActionComponent, AActor* ActorSpawned)
{
	if (ActionComponent == InActionComponent)
	{
		if (!CurrentActorsSpawned.Contains(ActorSpawned))
		{
			CurrentActorsSpawned.Add(ActorSpawned);
		}
	}
}

void ASpawner::OnActionActorDead(UActionComponent* InActionComponent, AActor* DeadActor)
{
	if (CurrentActorsSpawned.Contains(DeadActor))
	{
		CurrentActorsSpawned.Remove(DeadActor);
		DeadActor->Destroy();
	}
}

#pragma region Replication

void ASpawner::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASpawner, CurrentActorsSpawned);
}

#pragma endregion