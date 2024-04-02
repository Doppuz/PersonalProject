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

	void SetCurrentMovementState(EMovementState InState, bool SmoothTransition = false, float SmoothTransitionDuration = 1.f);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OnRep_CurrentMovementState();

protected:

#pragma region MovementeState

	UPROPERTY(ReplicatedUsing = "OnRep_CurrentMovementState", VisibleAnywhere, Category = "Movement State")
	EMovementState CurrentMovementState = EMovementState::WALKING;

	UPROPERTY(EditDefaultsOnly, meta = (ArraySizeEnum = "EMovementState"))
	float MovementStateSpeed[EMovementState::MAX]{ 900.f, 1800.f, 4000.f};

#pragma endregion

	class IMovementInterface* OwnerMovementInterface = nullptr;

	UPROPERTY()
	float InitialValueTransition = 0;

	UPROPERTY()
	float FinalValueTransition = 0;

	UPROPERTY()
	float SmoothSpeedForSecond = 0;

};
