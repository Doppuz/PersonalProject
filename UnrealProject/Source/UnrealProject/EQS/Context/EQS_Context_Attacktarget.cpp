// Fill out your copyright notice in the Description page of Project Settings.


#include "EQS_Context_Attacktarget.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "../../Controllers/BaseEnemyController.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void UEQS_Context_Attacktarget::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	UObject* QuerierObject = QueryInstance.Owner.Get();
	if ((QuerierObject == nullptr))
	{
		return;
	}

	APawn* CurrentPawn = Cast<APawn>(QuerierObject);

	if (CurrentPawn)
	{
		ABaseEnemyController* BaseEnemyController = Cast<ABaseEnemyController>(CurrentPawn->GetController());
		if (BaseEnemyController)
		{
			AActor* TargetActor = BaseEnemyController->GetCurrentAttackTarget();

			if (TargetActor)
			{
				UEnvQueryItemType_Actor::SetContextHelper(ContextData, TargetActor);
			}
		}
	}
}
