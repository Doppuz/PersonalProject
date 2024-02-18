// Fill out your copyright notice in the Description page of Project Settings.


#include "LichPlayerController.h"
#include "LichPlayerController.h"

void ALichPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetControlRotation(FRotator(-30.f, 0.f, 0.f));
}
