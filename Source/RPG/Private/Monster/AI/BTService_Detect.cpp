// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "BTService_Detect.h"


#include "RPG.h"
#include "EnemyBase.h"
#include "BehaviorTree/BlackboardComponent.h"

// Debug Message To Use
#include "Global.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.f;

	DetectAITypes.Add(Detect::CurLocationRadius);
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerAI, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerAI, NodeMemory, DeltaSeconds);

	auto EnemySelf = Cast<AEnemyBase>(OwnerAI.GetAIOwner()->GetPawn());
	RLOGCHECK(EnemySelf); // Checking -> Fast Return 
	bool bIsDebugPrint = EnemySelf->bDebugSearchSphereDraw;

	if (DetectAITypes.Num())
	{
		for (const auto& DetectType : DetectAITypes)
		{
			switch (DetectType)
			{
			case Detect::CurLocationRadius:
			{
				FVector Center = EnemySelf->GetActorLocation();

				if (auto World = EnemySelf->GetWorld())
				{

					TArray<FOverlapResult> DetectResults;
					FCollisionQueryParams CollisionQueryParam(NAME_None, false, EnemySelf);

					if (bool bResult = World->OverlapMultiByChannel(
						OUT DetectResults,
						Center,
						FQuat::Identity,
						ECollisionChannel::ECC_GameTraceChannel2,
						FCollisionShape::MakeSphere(EnemySelf->AIData.DetectLocationRadius),
						CollisionQueryParam
					))
					{
						for (auto& OverLapResult : DetectResults)
						{
							if (auto TargetPlayer = Cast<ARPGCharacter>(OverLapResult.GetActor()))
							{
								if (TargetPlayer->IsPlayerControlled())
								{
									OwnerAI.GetBlackboardComponent()->SetValueAsObject(AAIControllerBase::TargetKey, TargetPlayer);

									if (bIsDebugPrint == true)
									{
										DrawDebugSphere(World, Center, EnemySelf->AIData.DetectLocationRadius, 16, FColor::Green, false, 1.f);
										DrawDebugPoint(World, TargetPlayer->GetActorLocation(), 20.0f, FColor::Blue, false, 2.f);
										DrawDebugLine(World, EnemySelf->GetActorLocation(),
										TargetPlayer->GetActorLocation(), FColor::Blue, false, 1.0f);
									}
									return;
								}
							}
							else
								OwnerAI.GetBlackboardComponent()->SetValueAsObject(AAIControllerBase::TargetKey, nullptr);
						}
					}
				}
				if (bIsDebugPrint == true)
					DrawDebugSphere(GetWorld(), Center, EnemySelf->AIData.DetectLocationRadius, 16, FColor::Red, false, 1.f);
			}
			break;

			case Detect::EyesViewPort: {}; break;
			case Detect::SoundsRadius: {}; break;
			default:
				DebugScreenMessage(FString("DetectAITypes Param Error"), 3.f, FColor::Black);
				break;
			}
		}

	}
}