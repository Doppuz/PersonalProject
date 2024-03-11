// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

class UCapsuleComponent;
class UBillboardComponent;
class UActionComponent;

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

protected:

	UPROPERTY(EditAnywhere, Category = "Components")
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	UActionComponent* ActionComponent;

#if WITH_EDITORONLY_DATA

	UPROPERTY(EditAnywhere, Category = "Components")
	UBillboardComponent* EditorTexture;

#endif

};
