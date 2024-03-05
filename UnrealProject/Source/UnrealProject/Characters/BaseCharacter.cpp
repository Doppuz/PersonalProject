// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActionComponent = CreateDefaultSubobject<UActionComponent>(TEXT("ActionComponent"));
	StatsManager = CreateDefaultSubobject<UStatsManager>(TEXT("StatsManager"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

void ABaseCharacter::SetCurrentMovementSpeed(float InValue)
{
	GetCharacterMovement()->MaxWalkSpeed = InValue;
}

UMovementManager* ABaseCharacter::GetMovementManager()
{
	return nullptr;
}

#pragma endregion
