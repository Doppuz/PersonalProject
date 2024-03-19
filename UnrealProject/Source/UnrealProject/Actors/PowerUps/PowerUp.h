// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUp.generated.h"

class USphereComponent;
class UActionComponent;
class StaticMeshComponent;

class UAction;

UCLASS()
class UNREALPROJECT_API APowerUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region Events

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

#pragma endregion

protected:

	//Action added to the instigator when the power up is picked up
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	TArray<TSoftClassPtr<UAction>> ActionsToAdd;

	//Action added to the instigator when the power up is picked up
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aesthetic")
	float RotationSpeed = 100.f;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MakeEditWidget))
	FVector UpPosition = FVector(0.f, 0.f, 50.f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MakeEditWidget))
	FVector BotPosition = FVector(0.f, 0.f, -50.f);*/

#pragma region Components

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

#pragma endregion

};
