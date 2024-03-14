// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Components/BillboardComponent.h"	
#include "Components/CapsuleComponent.h"
#include "../Components/GeneralComponents/ActionComponent.h"
#include "Components/ArrowComponent.h"
#include "../Subsystem/WorldSubsystem/WorldSubsystem_GlobalEvents.h"

// Sets default values
ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;

#if WITH_EDITORONLY_DATA

	EditorTexture = CreateDefaultSubobject<UBillboardComponent>(TEXT("EditorTexture"));
	EditorTexture->SetupAttachment(RootComponent);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(RootComponent);

#endif

	ActionComponent = CreateDefaultSubobject<UActionComponent>(TEXT("ActionComponent"));
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	WS_GlobalEvents = GetWorld()->GetSubsystem<UWorldSubsystem_GlobalEvents>();

	if (ensureAlways(WS_GlobalEvents))
	{
		WS_GlobalEvents->OnActionSpawnActor.AddDynamic(this, &ASpawner::OnActionSpawnActor);
	}
}

void ASpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (ensureAlways(WS_GlobalEvents))
	{
		WS_GlobalEvents->OnActionSpawnActor.RemoveDynamic(this, &ASpawner::OnActionSpawnActor);
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
