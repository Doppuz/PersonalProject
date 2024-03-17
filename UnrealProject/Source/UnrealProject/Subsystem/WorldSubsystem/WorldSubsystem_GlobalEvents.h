// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "WorldSubsystem_GlobalEvents.generated.h"

class UActionComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatChanged, FStat_Broadcast, Stat_Broadcast);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionSpawnActor, UActionComponent*, InActionComponent, AActor*, ActorSpawned);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionActorDead, UActionComponent*, InActionComponent, AActor*, ActorSpawned);

UCLASS()
class UNREALPROJECT_API UWorldSubsystem_GlobalEvents : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "Stats")
	FOnStatChanged OnStatChanged;

	UPROPERTY(BlueprintAssignable, Category = "Stats")
	FOnActionSpawnActor OnActionSpawnActor;

	UPROPERTY(BlueprintAssignable, Category = "Stats")
	FOnActionActorDead OnActionActorDead;
	
};
