// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "..//GeneralComponents/MovementManager.h"
#include "InputAction.h"
#include "PlayerMovementManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJECT_API UPlayerMovementManager : public UMovementManager
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerMovementManager();

	void Move(const FInputActionValue& Value);

	void RotateCamera(const FInputActionValue& Value);

	void Jump(const FInputActionValue& Value);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:

	UPROPERTY()
	class AMainCharacter* MainCharacter = nullptr;;

	UPROPERTY(EditDefaultsOnly, Category = "Movement|Rotation", meta = (Displaypriority = 0))
	float MouseSensitivityX = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement|Rotation", meta = (Displaypriority = 1))
	float MouseSensitivityY = 1.f;

};
