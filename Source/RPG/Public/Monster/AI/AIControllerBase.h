// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerBase.generated.h"

/**
 *
 */
namespace Detect
{
	enum Type
	{
		EyesViewPort,
		CurLocationRadius,
		SoundsRadius,
	};
}

using DetectAIParams = TArray<Detect::Type>;

UCLASS()
class RPG_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	AAIControllerBase();
	virtual void OnPossess(APawn* Target)override;
	virtual void OnUnPossess()override;

	static const FName HomeKey;
	static const FName PatrolKey;
	static const FName TargetKey;

	FORCEINLINE static DetectAIParams GetDetectParams() { return DetectAIParams(); };
private:
	UPROPERTY()
		class UBehaviorTree* AITree;
	UPROPERTY()
		UBlackboardData* AIData;
};

