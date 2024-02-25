// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputAction.h"
#include "ShooterComponent.generated.h"

class ASquaredProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJECT_API UShooterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShooterComponent();

	bool Shoot();

	void Shoot_ByInput(const FInputActionValue& Value);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

#pragma region ShooterInterval

	UPROPERTY()
	FTimerHandle ShootTimerHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	float ShooterInterval = 1.f;

	UPROPERTY()
	bool bCanShoot = true;

#pragma endregion

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile", meta = (DisplaynName = "SquaredProjectile"))
	TSoftClassPtr<ABasicProjectile> BasicProjectileSoft;

	UPROPERTY()
	class USAGameInstance* GI = nullptr;

};
