// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "../Components/GeneralComponents/MovementManager.h"	
#include "Components/WidgetComponent.h"
#include "../UI/Health/HealthWidget.h"
#include "../Subsystem/WorldSubsystem/WorldSubsystem_GlobalEvents.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

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

		if (ensureAlways(HealthWidget))
		{
			HealthWidget->SetWidgetOwner(this);
		}
	}

	if (HasAuthority() && ensureAlways(WS_GlobalEvents))
	{
		WS_GlobalEvents->OnStopAction.AddDynamic(this, &ABaseEnemy::OnStopAction);
	}
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (HasAuthority() && ensureAlways(WS_GlobalEvents))
	{
		WS_GlobalEvents->OnStopAction.RemoveDynamic(this, &ABaseEnemy::OnStopAction);
	}
}

void ABaseEnemy::OnStopAction(UActionComponent* InActionComponent, FGameplayTag ActionName)
{
	if (InActionComponent == ActionComponent)
	{
		AAIController* AIController = Cast<AAIController>(GetController());

		if (AIController)
		{
			UBlackboardComponent* BC = AIController->GetBlackboardComponent();

			if (BC)
			{
				BC->SetValueAsString("LastStopAction", ActionName.ToString());
			}
		}
	}
}
