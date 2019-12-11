// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AIControllerBase.h"


#include "BehaviorTree/BTService.h"
#include "BTService_Detect.generated.h"

/**
 *
 */
UCLASS()
class RPG_API UBTService_Detect : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_Detect();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerAI, uint8* NodeMemory, float DeltaSeconds) override;

	// Detect 함수가 파라미터로 받을수 있다면 필요없는 멤버변수
	DetectAIParams DetectAITypes;
};
