// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "NotifyMeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UNotifyMeleeAttack : public UAnimNotify
{
	GENERATED_BODY()
	
protected:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BasicData")
	float AttackRange = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BasicData")
	float AttackRadius = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BasicData")
	float Damage = 20.f;

};
