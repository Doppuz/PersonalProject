// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SAPlayerState.generated.h"

class UWorldSubsystem_GlobalEvents;

UCLASS()
class UNREALPROJECT_API ASAPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	void UpdatePlayerScore(float AmountToAdd);

protected:

	virtual void BeginPlay() override;

#pragma region RPC

	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_UpdatePlayerScore(float OldValue, float NewValue);

#pragma endregion

protected:

	UPROPERTY()
	TObjectPtr<UWorldSubsystem_GlobalEvents> WS_GlobalEvents;

};
