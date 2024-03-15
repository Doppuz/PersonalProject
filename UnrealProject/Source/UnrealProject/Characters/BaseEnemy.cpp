// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "../Components/GeneralComponents/MovementManager.h"	
#include "Components/WidgetComponent.h"
#include "../UI/Health/HealthWidget.h"

ABaseEnemy::ABaseEnemy()
{
 	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthComponent"));
	HealthComponent->SetupAttachment(RootComponent);
	HealthComponent->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
	HealthComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthComponent->SetDrawSize(FVector2D(250.f, 5.f));	

	MovementManager = CreateDefaultSubobject<UMovementManager>(TEXT("MovementManager"));
}

#pragma region MovementInterface

UMovementManager* ABaseEnemy::GetMovementManager()
{
	return MovementManager;
}

#pragma endregion

#pragma region AttackDefenseInterface

float ABaseEnemy::GetAttackRange()
{
	return AttackRange;
}

float ABaseEnemy::GetDefenseRange()
{
	return DefenseRange;
}

#pragma endregion


// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	if (ensureAlways(HealthComponent))
	{
		UHealthWidget* HealthWidget = Cast<UHealthWidget>(HealthComponent->GetWidget());

		if (ensureAlways(HealthComponent))
		{
			HealthWidget->SetWidgetOwner(this);
		}
	}
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}