// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterComponent.h"
#include "../../Library/QuickAccessLibrary.h"
#include "../../GameInstance/ShooterGameInstance.h"
#include "../../SquaredProjectile.h"
#include "../../Interfaces/ShootInterface.h"

// Sets default values for this component's properties
UShooterComponent::UShooterComponent()
{
	PrimaryComponentTick.bCanEverTick = false;


}

bool UShooterComponent::Shoot()
{
	if (ensure(ShooterGameInstance))
	{
		ShooterGameInstance->StreamableManager.RequestAsyncLoad(SquaredProjectileSoft.ToSoftObjectPath(), [this]()
			{
				TSubclassOf<ASquaredProjectile> SquaredProjectileClass = SquaredProjectileSoft.Get();
				if (SquaredProjectileClass)
				{
					IShootInterface* ShootInterface = Cast<IShootInterface>(GetOwner());

					if (ShootInterface)
					{
						FActorSpawnParameters SpawnParameters;
						SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

						GetWorld()->SpawnActor<ASquaredProjectile>(SquaredProjectileClass, ShootInterface->GetShootStartingLocation(), FRotator::ZeroRotator, SpawnParameters);
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
	
	ShooterGameInstance = UQuickAccessLibrary::GetGameInstance(this);
}