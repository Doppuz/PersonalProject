// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasicProjectile.generated.h"

class UTagsReferenceSettings;

UCLASS(Blueprintable)
class UNREALPROJECT_API ABasicProjectile : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasicProjectile();

	UFUNCTION()
	FORCEINLINE float GetDamage() { return Damage; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void DestroyProjectile();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BasicData")
	float Damage = 20.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UParticleSystemComponent* ProjectileParticleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY()
	const UTagsReferenceSettings* TagsReferenceSettings;

	UPROPERTY()
	FTimerHandle DestroyTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timer")
	float DestroyTimerDuration = 3.f;
};
