// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Components/GeneralComponents/ActionComponent.h"
#include "../Components/GeneralComponents/StatsManager.h"
#include "../Subsystem/WorldSubsystem/WorldSubsystem_GlobalEvents.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ActionComponent = CreateDefaultSubobject<UActionComponent>(TEXT("ActionComponent"));
	StatsManager = CreateDefaultSubobject<UStatsManager>(TEXT("StatsManager"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetMesh())
	{
		MaterialInstanceDynamic = GetMesh()->CreateDynamicMaterialInstance(0);
	}

	WS_GlobalEvents = GetWorld()->GetSubsystem<UWorldSubsystem_GlobalEvents>();
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#pragma region MovementInterface

FVector ABaseCharacter::GetCurrentMovementSpeed()
{
	return GetCharacterMovement()->Velocity;
}

void ABaseCharacter::SetMaxMovementSpeed(float InValue)
{
	GetCharacterMovement()->MaxWalkSpeed = InValue;
}

float ABaseCharacter::GetCurrentMaxMovementSpeed()
{
	return GetCharacterMovement()->MaxWalkSpeed;
}

UMovementManager* ABaseCharacter::GetMovementManager()
{
	return nullptr;
}

#pragma endregion
