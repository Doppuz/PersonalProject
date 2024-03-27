// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "../../Enums/Enums_Stat.h"
#include "GameplayTagContainer.h"
#include "WorldSubsystem_GlobalEvents.generated.h"

class UActionComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatChanged, FStat_Broadcast, Stat_Broadcast);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionSpawnActor, UActionComponent*, InActionComponent, AActor*, ActorSpawned);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionActorDead, UActionComponent*, InActionComponent, AActor*, ActorSpawned);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStartAction, UActionComponent*, InActionComponent, FGameplayTag, ActionName);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStopAction, UActionComponent*, InActionComponent, FGameplayTag, ActionName);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAllPlayersReady, AGameModeBase*, CurrentGameMode);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnScoreUpdated, float, OldScore, float, NewScore);

UCLASS()
class UNREALPROJECT_API UWorldSubsystem_GlobalEvents : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "Stats")
	FOnStatChanged OnStatChanged;

	UPROPERTY(BlueprintAssignable, Category = "Action")
	FOnActionSpawnActor OnActionSpawnActor;

	UPROPERTY(BlueprintAssignable, Category = "Action")
	FOnActionActorDead OnActionActorDead;

	UPROPERTY(BlueprintAssignable, Category = "Action")
	FOnStartAction OnStartAction;

	UPROPERTY(BlueprintAssignable, Category = "Action")
	FOnStopAction OnStopAction;

	UPROPERTY(BlueprintAssignable, Category = "Login")
	FOnAllPlayersReady OnAllPlayersReady;

	UPROPERTY(BlueprintAssignable, Category = "Login")
	FOnScoreUpdated OnScoreUpdated;
	
};
