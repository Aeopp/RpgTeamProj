// Fill out your copyright notice in the Description page of Project Settings.
#include "EnemySkeleton.h"

#include "ConstructorHelpers.h"
#include "Components\SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components\CapsuleComponent.h"
#include "Animation/AnimBlueprint.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

AEnemySkeleton::AEnemySkeleton() : Super()
{
	SKMeshAssetPath = TEXT("SkeletalMesh'/Game/Resources/Monsters/Skeleton/Skeleton.Skeleton'");
	AnimAssetAttackPath = TEXT("AnimMontage'/Game/Resources/Monsters/Skeleton/Skeleton_Anim_SkeletonArmature_Skeleton_Attack_Montage.Skeleton_Anim_SkeletonArmature_Skeleton_Attack_Montage'");
	AnimAssetDeathPath = TEXT("AnimMontage'/Game/Resources/Monsters/Skeleton/Skeleton_Anim_SkeletonArmature_Skeleton_Death_Montage.Skeleton_Anim_SkeletonArmature_Skeleton_Death_Montage'");
	DeadBodyClassPath = TEXT("Blueprint'/Game/Resources/Monsters/Skeleton/DeadBodySkeleton.DeadBodySkeleton_C'");
	AnimBPAssetPath = TEXT("AnimBlueprint'/Game/Resources/Monsters/Skeleton/AnimBP_EnemySkeleton.AnimBP_EnemySkeleton'");
	AnimAssetSpawnPath = TEXT("AnimMontage'/Game/Resources/Monsters/Skeleton/Skeleton_Anim_SkeletonArmature_Skeleton_Spawn_Montage.Skeleton_Anim_SkeletonArmature_Skeleton_Spawn_Montage'");

	
	CurrentStat.Attack = 1.f;
	CurrentStat.AttackDistance = 200.f;
	CurrentStat.AttackRadius = 77.f;
	CurrentStat.AttackRatio = 1.7f;
	CurrentStat.Defense = 111111.f;
	CurrentStat.HP = 1.f;
	CurrentStat.Speed = 1111.f;

	
	GetCharacterMovement()->MaxWalkSpeed = CurrentStat.Speed  = 600.f;

	GetCapsuleComponent()->InitCapsuleSize(90.f, 120.f);
	GetMesh()->SetRelativeScale3D(FVector{ 0.6f,0.6f,0.6f });
	GetMesh()->SetRelativeLocation(FVector{ 20.f,0.f,-130.f });

	bDebugSearchSphereDraw = false;

	AIData.TrackingRotationVal = FMath::RandRange(AIData.MinTrackingRotationVal,AIData.MaxTrackingRotationVal);

	AIData.DetectLocationRadius = 5000.f;
	AIData.DetectSoundsRadius = 600.f;
	AIData.CanAttackRange = 300.f;
	AIData.FindPatrolLocationRadius = 5000.f;

	AIData.MinTrackingRotationVal = 3.f;
	AIData.MaxTrackingRotationVal = 5.f;

	AIData.TrackingRotationVal = FMath::RandRange(AIData.MinTrackingRotationVal, AIData.MaxTrackingRotationVal);
	// TrackingRotationVal = 
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SetSkMesh(*SKMeshAssetPath);

	if (SetSkMesh.Succeeded())
		GetMesh()->SetSkeletalMesh(SetSkMesh.Object);

	GetMesh()->SetAnimationMode(EAnimationMode::Type::AnimationBlueprint);

	static ConstructorHelpers::FObjectFinder<UAnimBlueprint>
		LoadAnimBP(*AnimBPAssetPath);

	UClass*const SetAnimBP = Cast<UClass>(LoadAnimBP.Object->GetAnimBlueprintGeneratedClass());

	if (SetAnimBP && LoadAnimBP.Succeeded())
		GetMesh()->SetAnimClass(SetAnimBP);

	static auto SetSpawm = ConstructorHelpers::FObjectFinder<UAnimMontage>(*AnimAssetSpawnPath);
	if (SetSpawm.Succeeded())
	{
		AnimMontageSpawn = SetSpawm.Object;
	}

	static auto SetAttack = ConstructorHelpers::FObjectFinder<UAnimMontage>(*AnimAssetAttackPath);
	if (SetAttack.Succeeded())
	{
		AnimMontageAttack = SetAttack.Object;
	}

	static auto SetDeath = ConstructorHelpers::FObjectFinder<UAnimMontage>(*AnimAssetDeathPath);
	if (SetAttack.Succeeded())
	{
		AnimMontageDeath = SetDeath.Object;
	}
}

void AEnemySkeleton::AttackProcess()
{
	// 공격 판정 함수 호출
	Super::AttackProcess();
}

void AEnemySkeleton::BeginPlay()
{
	Super::BeginPlay();

	if (AnimMontageSpawn)
	{
		if (auto AnimInstance = GetMesh()->GetAnimInstance())
		{
			AnimInstance->Montage_Play(AnimMontageSpawn);
		}
	}
}

void AEnemySkeleton::Hit()
{
	Super::Hit();
}

