// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "LichPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API ALichPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:

	ALichPlayerController();

	virtual void BeginPlay() override;

#pragma region IGenericTeamAgentInterface

	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;

	FORCEINLINE virtual FGenericTeamId GetGenericTeamId() const override { return TeamID; };

	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

#pragma endregion

private:

	UPROPERTY(EditAnywhere, Category = "TeamID")
	FGenericTeamId TeamID;

};
