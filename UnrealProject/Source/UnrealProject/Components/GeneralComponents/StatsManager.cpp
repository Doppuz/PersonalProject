// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsManager.h"
#include "../../Library/QuickAccessLibrary.h"
#include "../../GameInstance/SAGameInstance.h"
#include "../../Stats/Stat.h"
#include "../../Library/QuickAccessLibrary.h"

UStatsManager::UStatsManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UStatsManager::BeginPlay()
{
	Super::BeginPlay();

	GI = UQuickAccessLibrary::GetGameInstance(GetOwner());

	for (int i = 0; i < DefaultStats.Num(); i++)
	{
		AddStat(DefaultStats[i]);
	}
}

void UStatsManager::AddStat(TSoftClassPtr<UStat> StatSoftClass)
{
	if (ensureAlways(GI))
	{
		GI->StreamableManager.RequestAsyncLoad(StatSoftClass.ToSoftObjectPath(), [this, StatSoftClass]()
			{
				TSubclassOf<UStat> StatClass = StatSoftClass.Get();

				if (StatClass)
				{
					UStat* NewStat = NewObject<UStat>(this, StatClass);

					if (NewStat)
					{
						CurrentStats.Add(NewStat);

						NewStat->Initialize();
					}
				}
			});
	}
}

void UStatsManager::ChangeStat(AActor* Instigator, EStatCategory TargetStat, float Amount)
{
	for (int i = 0; i < CurrentStats.Num(); i++)
	{
		if (CurrentStats[i]->GetStatCategory() == TargetStat)
		{
			CurrentStats[i]->ChangeStat(Instigator, Amount);
		}
	}
}
