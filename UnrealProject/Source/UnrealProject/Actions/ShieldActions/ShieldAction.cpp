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
#include "../../Components/GeneralComponents/StatsManager.h"
#include "../../Enums/Enums_Stat.h"

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
		UStatsManager* OtherActorStatManager = Cast<UStatsManager>(ActionComponentOwner->GetOwner()->FindComponentByClass(UStatsManager::StaticClass()));

		if (ensureAlways(OtherActorStatManager))
		{
			OtherActorStatManager->ChangeStat(Instigator, EStatCategory::SHIELD, ShieldAmount);
		}

		ShieldComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		ShieldComponent->SetVisibility(true);

	}
}

void UShieldAction::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);

	if (ensureAlways(ActionComponentOwner) && ActionComponentOwner->GetOwner()->HasAuthority() &&
		ensureAlways(ShieldComponent) && ensureAlways(CapsuleComponent))
	{
		ShieldComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ShieldComponent->SetVisibility(false);

		ActionComponentOwner->RemoveAction(Instigator, this);
	}
}