// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsManager.generated.h"

class UStat;
class USAGameInstance;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJECT_API UStatsManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatsManager();

	void AddStat(TSoftClassPtr<UStat> StatSoftClass);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ChangeStat(AActor* Instigator, EStatCategory TargetStat, float Amount);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;
	
protected:

	//The initial stats could potentially be TSubclassOf
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats", meta = (DisplayPriority = 0))
	TArray<TSoftClassPtr<UStat>> DefaultStats;

	UPROPERTY(Replicated)
	TArray<UStat*> CurrentStats;

	UPROPERTY()
	TObjectPtr<USAGameInstance> GI;

};
