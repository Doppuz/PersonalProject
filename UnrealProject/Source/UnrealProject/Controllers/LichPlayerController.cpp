// Fill out your copyright notice in the Description page of Project Settings.


#include "LichPlayerController.h"

ALichPlayerController::ALichPlayerController()
{
	SetGenericTeamId(TeamID);
}

void ALichPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetControlRotation(FRotator(-30.f, 0.f, 0.f));
}

#pragma region IGenericTeamAgentInterface

ETeamAttitude::Type ALichPlayerController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const APawn* OtherPawn = Cast<APawn>(&Other))
	{
		if (IGenericTeamAgentInterface* GenericTeamAgentInterface = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			FGenericTeamId OtherGenericTeamID = GenericTeamAgentInterface->GetGenericTeamId();

			if (GetGenericTeamId() != OtherGenericTeamID)
			{
				return ETeamAttitude::Hostile;
			}
			else
			{
				return ETeamAttitude::Friendly;
			}
		}
	}

	return ETeamAttitude::Neutral;
}

void ALichPlayerController::SetGenericTeamId(const FGenericTeamId& InTeamID)
{
	if (HasAuthority())
	{
		TeamID = InTeamID;
	}
}

#pragma endregion