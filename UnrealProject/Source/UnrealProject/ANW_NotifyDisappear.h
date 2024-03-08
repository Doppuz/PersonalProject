// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifies/AnimNotify_PlayMontageNotify.h"
#include "ANW_NotifyDisappear.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UANW_NotifyDisappear : public UAnimNotify_PlayMontageNotifyWindow
{
	GENERATED_BODY()
	
protected:
		
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	void UpdateMaterialParam(USkeletalMeshComponent* MeshComp, float ValueToAdd);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Notify")
	FName MaterialParamName = "Dissolve";

	UPROPERTY()
	float NotifyDuration;

};
