// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolRoute.generated.h"

UCLASS()
class UNREALPROJECT_API APatrolRoute : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APatrolRoute();

	FVector GetlocationAtSplinePoint();

	void IncrementPatrolPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	int CurrentPatrolIndex = 0;

	UPROPERTY(EditInstanceOnly, BlueprintreadOnly, Category = "Route")
	int Direction = 1;

#pragma region Components

	UPROPERTY(EditAnywhere, Category = "Components")
	class USplineComponent* SplineComponent;

#pragma endregion

};
