// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "MainCharacter.generated.h"

class UPlayerInputComponent;
class UPlayerMovementManager;
class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent;

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

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PawnClientRestart() override;

	void PrimaryAttack();

	void Dash();

#pragma region Events

protected:

	UFUNCTION()
	void OnActionActorDead(UActionComponent* InActionComponent, AActor* DeadActor);

#pragma endregion

protected:

#pragma region Components

	UPROPERTY(EditAnywhere, Category = "Components")
	UPlayerInputComponent* CustomInputComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	UPlayerMovementManager* PlayerMovementManager;

	UPROPERTY(EditAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(EditAnywhere, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* ShieldComponent;

#pragma endregion


#pragma region Debug

	UFUNCTION(exec)
	void StartAction(FGameplayTag ActionName);

#pragma endregion

};
