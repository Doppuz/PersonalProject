// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputAction.h"
#include "GameplayTagContainer.h"
#include "PlayerInputComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJECT_API UPlayerInputComponent : public UActorComponent
{
	GENERATED_BODY()

	friend class AMainCharacter;

public:	
	// Sets default values for this component's properties
	UPlayerInputComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void PrepareInitialMappingContexts(class UEnhancedInputLocalPlayerSubsystem* Subsystem);

protected:

#pragma region Input

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced input")
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced input")
	class UInputAction* InputToMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced input")
	class UInputAction* InputToShoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced input")
	class UInputAction* InputToRotateCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced input")
	class UInputAction* InputToJump;

#pragma endregion

#pragma region SocketActionName

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tag")
	FGameplayTag PrimaryAttackTag;

#pragma endregion

};
