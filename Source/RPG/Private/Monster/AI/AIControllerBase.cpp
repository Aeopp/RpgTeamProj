// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AIControllerBase.h" 

// Debug Message Remove Plz
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
// Remove Plz


#include "NavigationSystem.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ConstructorHelpers.h"

const FName AAIControllerBase::HomeKey = TEXT("HomeLocation");
const FName AAIControllerBase::PatrolKey = TEXT("PatrolLocation");
const FName AAIControllerBase::TargetKey = TEXT("Target");

AAIControllerBase::AAIControllerBase()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData>SetUpAIData(TEXT("/Game/AI/BB_RPGEnemy.BB_RPGEnemy"));
	if (SetUpAIData.Succeeded()) { AIData = SetUpAIData.Object; }

	static ConstructorHelpers::FObjectFinder<UBehaviorTree>SetUpAITree(TEXT("/Game/AI/BT_RPGEnemy.BT_RPGEnemy"));
	if (SetUpAITree.Succeeded()) { AITree = SetUpAITree.Object; }
}
void AAIControllerBase::OnPossess(APawn* Target)
{
	Super::OnPossess(Target);
	if (UseBlackboard(AIData, Blackboard/*±âº»¸â¹öÀÓ!!*/))
	{
		Blackboard->SetValueAsVector(HomeKey, GetPawn()->GetActorLocation());
		if (RunBehaviorTree(AITree))
		{

		}
		else
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("AIController : couldn't Run AI Tree !! :"),
					false, FVector2D::UnitVector);
		}
	}
}

void AAIControllerBase::OnUnPossess()
{
	Super::OnUnPossess();
}