// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../../Enums/Enums_Movement.h"
#include "MovementManager.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJECT_API UMovementManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovementManager();

	void SetCurrentMovementState(EMovementState InState);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:

#pragma region MovementeState

	UPROPERTY()
	EMovementState CurrentMovementState = EMovementState::WALKING;

	UPROPERTY(EditDefaultsOnly, meta = (ArraySizeEnum = "EMovementState"))
	float MovementStateSpeed[EMovementState::MAX]{ 900.f, 1800.f, 4000.f};

#pragma endregion

	class IMovementInterface* OwnerMovementInterface = nullptr;

};
