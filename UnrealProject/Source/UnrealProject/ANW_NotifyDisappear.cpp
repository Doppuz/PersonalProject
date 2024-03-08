// Fill out your copyright notice in the Description page of Project Settings.


#include "ANW_NotifyDisappear.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Characters/BaseCharacter.h"

void UANW_NotifyDisappear::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp)
	{
		UpdateMaterialParam(MeshComp, 1.f);
		
		NotifyDuration = TotalDuration;
	}
}

void UANW_NotifyDisappear::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	UpdateMaterialParam(MeshComp, FrameDeltaTime / NotifyDuration);
}

void UANW_NotifyDisappear::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	UpdateMaterialParam(MeshComp, 0.f);
}

void UANW_NotifyDisappear::UpdateMaterialParam(USkeletalMeshComponent* MeshComp, float ValueToAdd)
{
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(MeshComp->GetOwner());

	if (BaseCharacter)
	{
		UMaterialInstanceDynamic* MaterialInstanceDynamic = BaseCharacter->GetMaterialInstanceDynamic();

		if (ensure(MaterialInstanceDynamic))
		{
			float CurrentValue = 0;
			MaterialInstanceDynamic->GetScalarParameterValue(MaterialParamName, CurrentValue);
			MaterialInstanceDynamic->SetScalarParameterValue(MaterialParamName, CurrentValue - ValueToAdd);
		}
	}
}
