// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "FindPatrolLocation.h"

#include "EnemyBase.h"
#include "AIControllerBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UFindPatrolLocation::UFindPatrolLocation()
{
	NodeName = TEXT("FindPatrolLocation");
}

EBTNodeResult::Type UFindPatrolLocation::ExecuteTask(UBehaviorTreeComponent& OwnerAI, uint8* Node)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerAI, Node);
	if (auto Enemy = Cast<AEnemyBase>(OwnerAI.GetAIOwner()->GetPawn()))
	{
		if (auto Navigation = UNavigationSystemV1::GetNavigationSystem(Enemy->GetWorld()))
		{
			FVector Origin = OwnerAI.GetBlackboardComponent()->GetValueAsVector(AAIControllerBase::HomeKey);
			FNavLocation NextPatrolLocation;

			if (Navigation->GetRandomPointInNavigableRadius(Enemy->GetActorLocation(), IN Enemy->AIData.FindPatrolLocationRadius, OUT NextPatrolLocation))
			{
				OwnerAI.GetBlackboardComponent()->SetValueAsVector(AAIControllerBase::PatrolKey, NextPatrolLocation.Location);

				Result = EBTNodeResult::Type::Succeeded;
			}
		}
		else
			Result = EBTNodeResult::Type::Failed;
	}
	else
		Result = EBTNodeResult::Type::Failed;

	return Result;
};

