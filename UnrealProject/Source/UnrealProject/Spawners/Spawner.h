// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UENUM(BlueprintType)
enum class ESpawnerType
{
	SINGLE,
	MULTIPLE,
	MAX UMETA(Hidden)
};


class UCapsuleComponent;
class UBillboardComponent;
class UActionComponent;
class UArrowComponent;

UCLASS()
class UNREALPROJECT_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

	bool CanSpawn();

	UFUNCTION()
	FORCEINLINE ESpawnerType GetSpawnerType() { return SpawnerType; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void OnActionSpawnActor(UActionComponent* InActionComponent, AActor* ActorSpawned);

	UFUNCTION()
	void OnActionActorDead(UActionComponent* InActionComponent, AActor* DeadActor);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner Info")
	ESpawnerType SpawnerType = ESpawnerType::SINGLE;

	UPROPERTY(replicated)
	TArray<AActor*> CurrentActorsSpawned;

//Components

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UActionComponent* ActionComponent;

#if WITH_EDITORONLY_DATA

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UBillboardComponent* EditorTexture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* ArrowComponent;

#endif

// end

	UPROPERTY()
	class UWorldSubsystem_GlobalEvents* WS_GlobalEvents;

};
