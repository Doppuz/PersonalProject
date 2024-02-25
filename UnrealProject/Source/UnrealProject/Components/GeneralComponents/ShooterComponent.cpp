// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterComponent.h"
#include "../../Library/QuickAccessLibrary.h"
#include "../../GameInstance/SAGameInstance.h"
#include "../../Projectiles/BasicProjectile.h"
#include "../../Interfaces/ShootInterface.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UShooterComponent::UShooterComponent()
{
	PrimaryComponentTick.bCanEverTick = false;


}

bool UShooterComponent::Shoot()
{
	if (ensure(GI))
	{
		GI->StreamableManager.RequestAsyncLoad(BasicProjectileSoft.ToSoftObjectPath(), [this]()
			{
				TSubclassOf<ABasicProjectile> BasicProjectileClass = BasicProjectileSoft.Get();
				if (BasicProjectileClass)
				{
					IShootInterface* ShootInterface = Cast<IShootInterface>(GetOwner());

					if (ShootInterface)
					{
						FActorSpawnParameters SpawnParameters;
						SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

						FTransform Transform(GetOwner()->GetActorRotation(), ShootInterface->GetShootStartingLocation());
						ABasicProjectile* BasicProjectile = GetWorld()->SpawnActorDeferred<ABasicProjectile>(BasicProjectileClass, Transform, GetOwner(), nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
					
						
						UGameplayStatics::FinishSpawningActor(BasicProjectile, Transform);
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("The owner does not implement the shoot interface"));
					}
				}
			});
	}

	return true;
}

void UShooterComponent::Shoot_ByInput(const FInputActionValue& Value)
{
	FTimerDelegate TimerDelegate;

	TimerDelegate.BindLambda([&]()
		{
		bCanShoot = true;
		});

	if (bCanShoot && !FMath::IsNearlyZero(Value[0]))
	{
		bCanShoot = false;
		Shoot();

		GetWorld()->GetTimerManager().SetTimer(
			ShootTimerHandle,
			TimerDelegate,
			ShooterInterval,
			false);
	}
}


// Called when the game starts
void UShooterComponent::BeginPlay()
{
	Super::BeginPlay();
	
	GI = UQuickAccessLibrary::GetGameInstance(this);
}