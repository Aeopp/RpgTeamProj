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
	// ���� ���� �ȿ� ������ �÷��̾��� ��ġ��� �󸶳� ���� ȸ������ �� ( �������� ���ϱ� ������� )
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float TrackingRotationVal;
	// ���� ���� �Ǵ� �Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float CanAttackRange = 200.f;
	// �÷��̾� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float DetectLocationRadius = 600.f;
	// �÷��̾� ���� �Ҹ� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float DetectSoundsRadius = 400.f;
	// ���� ��Ʈ�� �Ÿ� ã���� ���� �����̼� ���κ����� ����
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

	// AI ���� ���� �Ǵ��� �Ͽ��� ���� �ϴ� �ִϸ��̼Ǹ� ȣ���ϰ� ������ �ִϸ��̼ǿ��� 
	// �ǰ� ������ �� ���� ���� (��κ� ���� �ִϸ��̼��� ������ �κ� )��Ƽ���̸� �ɾ ��Ƽ���̿��� ���� �ǰ� ������ ȣ��
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


