// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "BTTask_TurnToTarget.h"

#include "RPGCharacter.h"
#include "AIControllerBase.h"
#include "EnemyBase.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget() :Super()
{
	NodeName = TEXT("Turn");
};

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	if (auto Enemy = Cast<AEnemyBase>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		if (auto Target = Cast<ARPGCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AAIControllerBase::TargetKey)))
		{
			if (Enemy->CurState == EState::Deathed)
			{
				return EBTNodeResult::Failed;
			}

			FVector LookVec = Target->GetActorLocation() - Enemy->GetActorLocation();

			FRotator LookRot = FRotationMatrix::MakeFromX(LookVec).Rotator();

			Enemy->SetActorRotation(FMath::RInterpTo(Enemy->GetActorRotation(), LookRot, GetWorld()->GetDeltaSeconds(), Enemy->AIData.TrackingRotationVal));

			return EBTNodeResult::Succeeded;
		}
		else return EBTNodeResult::Failed;
	}
	else return EBTNodeResult::Failed;

	return Result;
}
