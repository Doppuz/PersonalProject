// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Components/BillboardComponent.h"	
#include "Components/CapsuleComponent.h"
#include "../Components/GeneralComponents/ActionComponent.h"
#include "Components/ArrowComponent.h"

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
	
}
