// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldAction.h"
#include "../../Components/GeneralComponents/ActionComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GenericTeamAgentInterface.h"
#include "../../Library/QuickAccessLibrary.h"
#include "../../Projectiles/BasicProjectile.h"
#include "../../Enums/SACustomDefine.h"
#include "../../Characters/MainCharacter.h"
#include "Net/UnrealNetwork.h"

void UShieldAction::Initialize(UActionComponent* NewActionComp)
{
	Super::Initialize(NewActionComp);

	if (ensureAlways(ActionComponentOwner) && ActionComponentOwner->GetOwner()->HasAuthority())
	{
		ShieldComponent = Cast<UStaticMeshComponent>(ActionComponentOwner->GetOwner()->GetDefaultSubobjectByName(TEXT("ShieldComponent")));
		CapsuleComponent = Cast<UCapsuleComponent>(ActionComponentOwner->GetOwner()->GetComponentByClass(UCapsuleComponent::StaticClass()));
	}
}

void UShieldAction::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	if (ensureAlways(ActionComponentOwner) && ActionComponentOwner->GetOwner()->HasAuthority() &&
		ensureAlways(ShieldComponent) && ensureAlways(CapsuleComponent))
	{
		ShieldComponent->OnComponentBeginOverlap.AddDynamic(this, &UShieldAction::OnComponentBeginOverlap);
		ShieldComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		ShieldComponent->SetVisibility(true);

		CapsuleComponent->SetCollisionResponseToChannel(ECC_Projectile, ECollisionResponse::ECR_Ignore);
	}
}

void UShieldAction::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);

	if (ensureAlways(ActionComponentOwner) && ActionComponentOwner->GetOwner()->HasAuthority() &&
		ensureAlways(ShieldComponent) && ensureAlways(CapsuleComponent))
	{
		ShieldComponent->OnComponentBeginOverlap.RemoveDynamic(this, &UShieldAction::OnComponentBeginOverlap);
		ShieldComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ShieldComponent->SetVisibility(false);

		CapsuleComponent->SetCollisionResponseToChannel(ECC_Projectile, ECollisionResponse::ECR_Overlap);

		ActionComponentOwner->RemoveAction(Instigator, this);
	}
}

void UShieldAction::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ensureAlways(ActionComponentOwner) && OtherActor)
	{
		ETeamAttitude::Type TeamAttitudeType = QL::GetTeamAttitude(this, ActionComponentOwner->GetOwner(), OtherActor->GetInstigator());

		if (TeamAttitudeType == ETeamAttitude::Hostile || TeamAttitudeType == ETeamAttitude::Neutral)
		{
			//temporal
			ABasicProjectile* BasicProjectile = Cast<ABasicProjectile>(OtherActor);

			if (BasicProjectile)
			{
				CurrentDamage += BasicProjectile->GetDamage();
				BasicProjectile->Destroy();

				if (CurrentDamage >= ShieldHealth)
				{
					StopAction_Implementation(ActionComponentOwner->GetOwner());
				}
			}
		}
	}
}

#pragma region Replication

void UShieldAction::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UShieldAction, CurrentDamage);
}

#pragma endregion