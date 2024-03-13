// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:

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

};
