// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interfaces/MovementInterface.h"
#include "BaseCharacter.generated.h"

class UActionComponent;

UCLASS()
class UNREALPROJECT_API ABaseCharacter : public ACharacter, public IMovementInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

#pragma region MovementInterface

	virtual FVector GetCurrentMovementSpeed();

	virtual void SetCurrentMovementSpeed(float Invalue);

	virtual class UMovementManager* GetMovementManager();

#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, Category = "Components")
	UActionComponent* ActionComponent = nullptr;
};
