// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "../Interfaces/ShootInterface.h"
#include "MainCharacter.generated.h"

UCLASS()
class UNREALPROJECT_API AMainCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

#pragma region MovementInterface

	virtual class UMovementManager* GetMovementManager() override;

#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PawnClientRestart() override;

	void PrimaryAttack();

protected:

#pragma region Components

	UPROPERTY(EditAnywhere, Category = "Components")
	class UPlayerInputComponent* CustomInputComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UPlayerMovementManager* PlayerMovementManager;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(EditAnywhere, Category = "Components")
	class UCameraComponent* CameraComponent;

#pragma endregion

};
