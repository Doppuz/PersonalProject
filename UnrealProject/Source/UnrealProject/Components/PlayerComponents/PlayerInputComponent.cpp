// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values for this component's properties
UPlayerInputComponent::UPlayerInputComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UPlayerInputComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UPlayerInputComponent::PrepareInitialMappingContexts(UEnhancedInputLocalPlayerSubsystem* Subsystem)
{
	if (Subsystem)
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}
