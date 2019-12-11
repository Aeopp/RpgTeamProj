// Fill out your copyright notice in the Description page of Project Settings.
#include "EnemyBat.h"

#include "Components\SkeletalMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Components\SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components\CapsuleComponent.h"
#include "Animation/AnimBlueprint.h"
#include "Animation/AnimInstance.h"


AEnemyBat::AEnemyBat() : Super()
{
	SKMeshAssetPath = TEXT("SkeletalMesh'/Game/Resources/Monsters/Bat/Bat_Bat.Bat_Bat'");
	AnimBPAssetPath = TEXT("AnimBlueprint'/Game/Resources/Monsters/Bat/Bat_Bat_Skeleton_AnimBlueprint.Bat_Bat_Skeleton_AnimBlueprint'");
	AnimAssetAttack2Path = TEXT("AnimMontage'/Game/Resources/Monsters/Bat/Bat_Bat_Anim_BatArmature_Bat_Attack2_Montage.Bat_Bat_Anim_BatArmature_Bat_Attack2_Montage'");
	AnimAssetHitPath = TEXT("AnimMontage'/Game/Resources/Monsters/Bat/Bat_Bat_Anim_BatArmature_Bat_Hit_Montage.Bat_Bat_Anim_BatArmature_Bat_Hit_Montage'");
	AnimAssetDeathPath = TEXT("AnimMontage'/Game/Resources/Monsters/Bat/Bat_Bat_Anim_BatArmature_Bat_Death_Montage.Bat_Bat_Anim_BatArmature_Bat_Death_Montage'");
	AnimAssetAttackPath = TEXT("AnimMontage'/Game/Resources/Monsters/Bat/Bat_Bat_Anim_BatArmature_Bat_Attack_Montage.Bat_Bat_Anim_BatArmature_Bat_Attack_Montage'");
	DeadBodyClassPath = TEXT("Blueprint'/Game/Resources/Monsters/Bat/BatDeadBody.BatDeadBody_C'");

	AnimMontageAttack2 = CreateDefaultSubobject<UAnimMontage>(TEXT("AnimAttack2"));
	AnimMontageHit = CreateDefaultSubobject<UAnimMontage>(TEXT("AnimHit"));

	//   AI 지배 ( 레벨 배치 or 스폰 )
	
	CurrentStat.Attack = 10.f;
	CurrentStat.AttackDistance = 100.f;
	CurrentStat.AttackRadius = 50.f;
	CurrentStat.AttackRatio = 3.f;
	CurrentStat.Defense = 44.f;
	CurrentStat.HP = 50.f;


	AIData.DetectLocationRadius = 5000.f;
	AIData.DetectSoundsRadius = 400.f;
	AIData.CanAttackRange = 200.f;
	AIData.FindPatrolLocationRadius = 5000.f;


	AIData.MinTrackingRotationVal = 3.f;
	AIData.MaxTrackingRotationVal = 5.f;

	AIData.TrackingRotationVal = FMath::RandRange(AIData.MinTrackingRotationVal, AIData.MaxTrackingRotationVal);
	// TrackingRotationVal = 


	GetCharacterMovement()->MaxWalkSpeed = CurrentStat.Speed = 350.f;
	GetCapsuleComponent()->InitCapsuleSize(90.f, 120.f);
	GetMesh()->SetRelativeScale3D(FVector{ 0.5f,0.5f,0.5f });
	GetMesh()->SetRelativeLocation(FVector{ 20.f,0.f,-130.f });

	// AI 플레이어 감지 거리 디버깅 용
	bDebugSearchSphereDraw = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SetUpSKMesh(*SKMeshAssetPath);

	if (SetUpSKMesh.Succeeded())
		GetMesh()->SetSkeletalMesh(SetUpSKMesh.Object);

	// Animation Blueprint 로 세팅
	GetMesh()->SetAnimationMode(EAnimationMode::Type::AnimationBlueprint);


	static ConstructorHelpers::FObjectFinder<UAnimBlueprint>
		LoadAnimBP(*AnimBPAssetPath);

	UClass*const SetAnimBP = Cast<UClass>(LoadAnimBP.Object->GetAnimBlueprintGeneratedClass());

	GetMesh()->SetAnimInstanceClass(SetAnimBP);


	static  ConstructorHelpers::FObjectFinder<UAnimMontage>SetAttack2
	(*AnimAssetAttack2Path);

	if (SetAttack2.Succeeded())
	{
		AnimMontageAttack2 = SetAttack2.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SetHit(*AnimAssetHitPath);

	if (SetHit.Succeeded())
	{
		AnimMontageHit = SetHit.Object;
	}

	static auto SetAttack1 = ConstructorHelpers::FObjectFinder<UAnimMontage>(*AnimAssetAttackPath);
	if (SetAttack1.Succeeded())
	{
		AnimMontageAttack = SetAttack1.Object;
	}

	static auto SetDeathPath = ConstructorHelpers::FObjectFinder<UAnimMontage>(*AnimAssetDeathPath);
	if (SetDeathPath.Succeeded())
	{
		AnimMontageDeath = SetDeathPath.Object;
	}

	OnAttackProcessDelegate2Bat.AddDynamic(this,&AEnemyBat::AttackProcess);
}

void AEnemyBat::AttackProcess()
{
	// 공격 판정 함수 호출
	Super::AttackProcess();
}

void AEnemyBat::Hit()
{
	Super::Hit();

	if (AnimMontageHit)
	{
		if (auto AnimInstance = GetMesh()->GetAnimInstance())
		{
			AnimInstance->Montage_Play(AnimMontageHit);
		}
	}
}

void AEnemyBat::Attack()
{
	Super::Attack();

	if (auto AnimInstance = GetMesh()->GetAnimInstance())
	{
		if (AnimMontageAttack && AnimMontageAttack2)
		{
			int32 AttackNumber = FMath::RandRange(1, 2);

			if (AttackNumber == 1)
			{
				AnimInstance->Montage_Play(AnimMontageAttack);
			}
			else if (AttackNumber == 2)
			{
				AnimInstance->Montage_Play(AnimMontageAttack2);
			}
		}
	}
}


