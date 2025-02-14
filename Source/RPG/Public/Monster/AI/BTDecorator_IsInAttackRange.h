// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsInAttackRange.generated.h"

/**
 *
 */
UCLASS()
class RPG_API UBTDecorator_IsInAttackRange : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTDecorator_IsInAttackRange();
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerAI, uint8* Node)const override;
};
