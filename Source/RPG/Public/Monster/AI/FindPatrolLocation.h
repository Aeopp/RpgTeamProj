// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"




#include "FindPatrolLocation.generated.h"

/**
 *
 */
UCLASS()
class RPG_API UFindPatrolLocation : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UFindPatrolLocation();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerAI, uint8* Node)override;
};
