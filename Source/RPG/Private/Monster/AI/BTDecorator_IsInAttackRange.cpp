// Fill out your copyright notice in the Description page of Project Settings.
#include "BTDecorator_IsInAttackRange.h"


#include "AIControllerBase.h"
#include "EnemyBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "RPGCharacter.h"

//Debug Message To Use
#include "Global.h"
// Remove

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}
bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerAI, uint8* Node) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerAI, Node);

	auto Enemy = Cast<AEnemyBase>(OwnerAI.GetAIOwner()->GetPawn());

	auto Target = Cast<ARPGCharacter>(OwnerAI.GetBlackboardComponent()->GetValueAsObject(AAIControllerBase::TargetKey));

	if (Enemy && Target)
	{
		bResult = Target->GetDistanceTo(Enemy) <= Enemy->AIData.CanAttackRange;

		if (bResult == true)
		{
			// 내가 공격중이 아닐때만 공격
			if (Enemy->CurState != EState::Attacking)
			{
				Enemy->Attack();
			}
			return true;
		}
		else return false;
	}
	else return false;

	return bResult;
}

