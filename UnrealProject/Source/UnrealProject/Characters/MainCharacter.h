// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interfaces/ShootInterface.h"
#include "MainCharacter.generated.h"

UCLASS()
class UNREALPROJECT_API AMainCharacter : public ACharacter, public IShootInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

#pragma region ShooterInterface

	virtual FVector GetShootStartingLocation();

#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PawnClientRestart() override;

protected:

#pragma region Components

	UPROPERTY(VisibleAnywhere)
	class UPlayerInputComponent* CustomInputComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UMovementManager* MovementManager;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(EditAnywhere, Category = "Components")
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UShooterComponent* ShooterComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* ShootPoint;

#pragma endregion

};
