// Fill out your copyright notice in the Description page of Project Settings.
#include "EnemyBase.h"

#include "AIControllerBase.h"
#include "Components\CapsuleComponent.h"
#include "GameFramework\SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Animation/AnimationAsset.h"
#include "Components\SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Engine/World.h"
// Debug Only
#include "Global.h"
// Debug End

AEnemyBase::AEnemyBase() : ACharacterBase()
{
	//   AI 지배 ( 레벨 배치 or 스폰 )
	AIControllerClass = AAIControllerBase::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;

	// GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);

	GetCharacterMovement()->MaxWalkSpeed = CurrentStat.Speed;

	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	GetCapsuleComponent()->InitCapsuleSize(90.f, 120.f);
	GetMesh()->SetRelativeScale3D(FVector{ 0.5f,0.5f,0.5f });
	GetMesh()->SetRelativeLocation(FVector{ 20.f,0.f,-130.f });

	bDebugSearchSphereDraw = false;

	/*	상속받는 객체들의 특징별로 다르게 세팅하면 좋을 만한 값들
	GetCharacterMovement()->MaxWalkSpeed = 350.f;
	GetCapsuleComponent()->InitCapsuleSize(90.f, 120.f);
	GetMesh()->SetRelativeScale3D(FVector{ 0.5f,0.5f,0.5f });
	GetMesh()->SetRelativeLocation(FVector{ 20.f,0.f,-130.f });
	bDebugSearchSphereDraw = true;
	GetMesh()->SetAnimationMode(EAnimationMode::Type::AnimationSingleNode);
	*/

	AIData.TrackingRotationVal= FMath::RandRange(AIData.MinTrackingRotationVal, AIData.MaxTrackingRotationVal);

	AnimMontageAttack = CreateDefaultSubobject<UAnimMontage>(TEXT("EnemyAnimMontageAttack"));
	AnimMontageDeath = CreateDefaultSubobject<UAnimMontage>(TEXT("EnemyAnimMontageDeath"));

	//OnAttackProcessDelegate.AddDynamic(this, &ACharacterBase::AttackProcess);
	//OnDeathDelegate.AddDynamic(this, &ACharacterBase::Death);
};

void AEnemyBase::Attack()
{
	Super::Attack();

	if (auto AnimInstance = GetMesh()->GetAnimInstance())
	{
		if (AnimMontageAttack)
		{
			AnimInstance->Montage_Play(AnimMontageAttack);
		}
	}
}

void AEnemyBase::AttackProcess()
{
	// 부모 공격 판정 함수 호출 하기
	ACharacterBase::AttackProcess();
}

void AEnemyBase::Hit()
{
	ACharacterBase::Hit();
}

void AEnemyBase::Death()
{
	ACharacterBase::Death();

	if (auto AnimInstance = GetMesh()->GetAnimInstance())
	{
		if (AnimMontageDeath)
		{
			AnimInstance->Montage_Play(AnimMontageDeath);
		}
	}

	UClass* DeadBodySpawn = StaticLoadClass(AActor::StaticClass(), NULL, *DeadBodyClassPath);
	FTransform SpawnTransform = GetTransform();

	if (DeadBodySpawn)
	{
		auto DeadBodyClone = 	GetWorld()->SpawnActor<AActor>(DeadBodySpawn, SpawnTransform);
		DeadBodyClone->SetLifeSpan(5.f);
	}

	Destroy();
}

