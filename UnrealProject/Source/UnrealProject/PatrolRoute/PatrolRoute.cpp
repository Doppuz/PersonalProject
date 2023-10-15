// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolRoute.h"
#include "Components/SplineComponent.h"

// Sets default values
APatrolRoute::APatrolRoute()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
}

FVector APatrolRoute::GetlocationAtSplinePoint()
{
	bool bIsMinIndex = CurrentPatrolIndex >= 0;
	bool bIsLessThanMaxIndex = SplineComponent->GetNumberOfSplinePoints() - 1 >= CurrentPatrolIndex;
	
	if (bIsMinIndex && bIsLessThanMaxIndex)
	{
		return SplineComponent->GetWorldLocationAtSplinePoint(CurrentPatrolIndex);
	}

	return FVector::ZeroVector;
}

// Called when the game starts or when spawned
void APatrolRoute::BeginPlay()
{
	Super::BeginPlay();
	
}

void APatrolRoute::IncrementPatrolPoint()
{
	CurrentPatrolIndex += Direction;
	
	int NumberOfSplinePoint = SplineComponent->GetNumberOfSplinePoints();

	if (CurrentPatrolIndex >= NumberOfSplinePoint - 1)
	{
		Direction = -1;
	}
	else if(CurrentPatrolIndex == 0)
	{
		Direction = +1;
	}
}
