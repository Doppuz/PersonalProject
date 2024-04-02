// Fill out your copyright notice in the Description page of Project Settings.


#include "DashAction.h"
#include "../../Components/GeneralComponents/ActionComponent.h"
#include "../../Interfaces/MovementInterface.h"
#include "Gameframework/Character.h"
#include "Gameframework/CharacterMovementComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

void UDashAction::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	if (ensureAlways(ActionComponentOwner))
	{
		ACharacter* Character = Cast<ACharacter>(ActionComponentOwner->GetOwner());
		IMovementInterface* MovementInterface = Cast<IMovementInterface>(Character);

		if (Character && Character->GetCharacterMovement() && ensureAlways(MovementInterface))
		{
			FVector CurrentDirection = Character->GetCharacterMovement()->Velocity;
			CurrentDirection.Normalize();

			if (Character->HasAuthority())
			{
				Character->LaunchCharacter(CurrentDirection * DashDistance, true, false);
			}

			if (Character->GetCharacterMovement()->Velocity != FVector::ZeroVector && DashEffect && Character->GetMesh())
			{
				UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DashEffect, Character->GetMesh()->GetSocketLocation(DashEffectSocketName), CurrentDirection.Rotation(), DashEffectScale, true, false);
					
				if (NiagaraComp)
				{
					NiagaraComp->SetCustomTimeDilation(DashEffectSpeed);
					NiagaraComp->Activate();
				}
			}

			if (ensureAlways(GetWorld()))
			{
				FTimerDelegate RespawnDelegate = FTimerDelegate::CreateUObject(this, &UDashAction::StopAction_Implementation, Instigator);
				GetWorld()->GetTimerManager().SetTimer(DashTimerHandle, RespawnDelegate, DashDuration, false);
			}
		}
	}
}

void UDashAction::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);
}
