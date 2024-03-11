// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "../Components/PlayerComponents/PlayerInputComponent.h"
#include "../Components/PlayerComponents/PlayerMovementManager.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../Components/GeneralComponents/ActionComponent.h"
#include "Camera/CameraActor.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	CustomInputComponent = CreateDefaultSubobject<UPlayerInputComponent>(TEXT("InputComponent"));
	PlayerMovementManager = CreateDefaultSubobject<UPlayerMovementManager>(TEXT("PlayerMovementManager"));
}

#pragma region MovementInterface

UMovementManager* AMainCharacter::GetMovementManager()
{
	return PlayerMovementManager;
}

#pragma endregion

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(CustomInputComponent->InputToMove, ETriggerEvent::Triggered, PlayerMovementManager, &UPlayerMovementManager::Move);
	EnhancedInputComponent->BindAction(CustomInputComponent->InputToRotateCamera, ETriggerEvent::Triggered, PlayerMovementManager, &UPlayerMovementManager::RotateCamera);
	EnhancedInputComponent->BindAction(CustomInputComponent->InputToJump, ETriggerEvent::Triggered, PlayerMovementManager, &UPlayerMovementManager::Jump);
	EnhancedInputComponent->BindAction(CustomInputComponent->InputToShoot, ETriggerEvent::Triggered, this, &AMainCharacter::PrimaryAttack);
}

void AMainCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	if (ensure(CustomInputComponent))
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			// Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller.
			CustomInputComponent->PrepareInitialMappingContexts(ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()));
		}
	}
}

void AMainCharacter::PrimaryAttack()
{
	ActionComponent->StartActionByName(this, CustomInputComponent->PrimaryAttackTag);
}