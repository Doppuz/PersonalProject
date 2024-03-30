// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:

	ABaseAIController();

	virtual void OnPossess(APawn* InPawn) override;

	void StopBehaviorTree();

	UFUNCTION()
	FORCEINLINE UBehaviorTree* GetBehaviorTree() { return BehaviorTree; };

#pragma region IGenericTeamAgentInterface

	virtual void SetGenericTeamId(const FGenericTeamId& InTeamID) override;

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const;

#pragma endregion

protected:

	UPROPERTY(EditAnywhere, BlueprintreadWrite, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintreadWrite, Category = "AI")
	class UAIPerceptionComponent* AIPerceptionComponent;

private:

	UPROPERTY(EditAnywhere, Category = "AI")
	FGenericTeamId TeamID;

#pragma region Senses

protected:

	void HandleSightSense(AActor* Actor, FAIStimulus Stimulus);

	void HandleHearingSense(AActor* Actor, FAIStimulus Stimulus);

	void HandleOutOfSightSense(AActor* Actor, FAIStimulus Stimulus);

	void HandleHearingExpiresSense(AActor* Actor, FAIStimulus Stimulus);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UAISenseConfig_Sight* SightConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UAISenseConfig_Hearing* HearingConfig;

#pragma endregion

};
