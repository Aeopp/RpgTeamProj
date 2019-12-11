// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Components\SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterBase.h"
#include "CoreMinimal.h"
#include "RPGCharacter.h"
#include "EnemyBase.generated.h"

USTRUCT(BlueprintType,Blueprintable)
struct FAIData
{
	GENERATED_USTRUCT_BODY()
	// 공격 범위 안에 있을시 플레이어의 위치대로 얼마나 빨리 회전할지 값 ( 높을수록 피하기 어려워짐 )
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float TrackingRotationVal;
	// 공격 가능 판단 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float CanAttackRange = 200.f;
	// 플레이어 감지 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float DetectLocationRadius = 600.f;
	// 플레이어 감지 소리 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float DetectSoundsRadius = 400.f;
	// 랜덤 패트롤 거리 찾을때 현재 로케이션 으로부터의 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float FindPatrolLocationRadius = 2000.f;

	float MinTrackingRotationVal = 2.f;
	float MaxTrackingRotationVal = 4.f;
};

/**
 *
 */
UCLASS()
class RPG_API AEnemyBase : public ACharacterBase
{
	GENERATED_BODY()
protected:
	FString AnimAssetDeathPath;
	FString AnimAssetAttackPath;
	FString DeadBodyClassPath;
	FString AnimBPAssetPath;
	FString SKMeshAssetPath;
public:
	AEnemyBase();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DebugTest)
	bool bDebugSearchSphereDraw = true;

	//UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = CustomDelegate)
	//FOnAttackProcessDelegate OnAttackProcessDelegate;
	//UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = CustomDelegate)
	//FOnDeathDelegate OnDeathDelegate;

	FORCEINLINE void ActiveFalse()
	{
		GetMesh()->SetActive(false);
		GetCharacterMovement()->SetActive(false);
	}

	// AI 에서 공격 판단을 하였을 때는 일단 애니메이션만 호출하고 실제로 애니메이션에서 
	// 피격 판정을 할 만한 곳에 (대부분 공격 애니메이션이 끝나는 부분 )노티파이를 걸어서 노티파이에서 실제 피격 판정을 호출
		virtual void Attack()override;
		virtual void AttackProcess()override;
		virtual void Death()override;
		virtual void Hit()override;

	UPROPERTY()
		class UAnimMontage* AnimMontageAttack;
	UPROPERTY()
		class UAnimMontage* AnimMontageDeath;

	UPROPERTY(EditAnywhere, Category = AI)
	FAIData AIData;
};


