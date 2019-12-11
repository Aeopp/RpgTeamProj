// Fill out your copyright notice in the Description page of Project Settings.
#include "EnemyDragon.h"

#include "Components\SkeletalMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Components\SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components\CapsuleComponent.h"
#include "Animation/AnimBlueprint.h"
#include "Animation/AnimInstance.h"



AEnemyDragon::AEnemyDragon() : Super()
{
	SKMeshAssetPath = TEXT("/Game/Resources/Monsters/Dragon/Dragon_Dragon.Dragon_Dragon");
	AnimBPAssetPath = TEXT("/Game/Resources/Monsters/Dragon/AnimBP_EnemyDragon.AnimBP_EnemyDragon");
	AnimAssetAttack2Path = TEXT("/Game/Resources/Monsters/Dragon/AnimMontage_Dragon_Attack2.AnimMontage_Dragon_Attack2");
	AnimAssetHitPath = TEXT("/Game/Resources/Monsters/Dragon/AnimMontage_Dragon_Hit.AnimMontage_Dragon_Hit");
	AnimAssetDeathPath = TEXT("AnimMontage'/Game/Resources/Monsters/Dragon/AnimMontage_Dragon_Death.AnimMontage_Dragon_Death'");
	AnimAssetAttackPath = TEXT("AnimMontage'/Game/Resources/Monsters/Dragon/AnimMontage_Dragon_Attack1.AnimMontage_Dragon_Attack1'");
	DeadBodyClassPath = TEXT("Blueprint'/Game/Resources/Monsters/Dragon/DragonDeadBody.DragonDeadBody_C'");

	AnimMontageAttack2 = CreateDefaultSubobject<UAnimMontage>(TEXT("AnimAttack2"));
	AnimMontageHit = CreateDefaultSubobject<UAnimMontage>(TEXT("AnimHit"));

	CurrentStat.Attack = 50.f;
	CurrentStat.AttackDistance = 500.f;
	CurrentStat.AttackRadius = 77.f;
	CurrentStat.AttackRatio = 5.f;
	CurrentStat.Defense = 50.f;
	CurrentStat.HP = 777.f;

	GetCharacterMovement()->MaxWalkSpeed  = CurrentStat.Speed = 500.f;

	GetCapsuleComponent()->InitCapsuleSize(150.f, 150.f);
	GetMesh()->SetRelativeScale3D(FVector{ 1.0f,1.0f,1.0f });
	GetMesh()->SetRelativeLocation(FVector{ 20.f,0.f,-130.f });

	bDebugSearchSphereDraw = false;

	AIData.MinTrackingRotationVal = 3.f;
	AIData.MaxTrackingRotationVal = 5.f;

	AIData.TrackingRotationVal = FMath::RandRange(AIData.MinTrackingRotationVal,AIData.MaxTrackingRotationVal);
	AIData.FindPatrolLocationRadius = 5000.f;

	AIData.DetectLocationRadius = 5000.f;
	AIData.DetectSoundsRadius = 800.f;
	AIData.CanAttackRange = 300.f;

	// TrackingRotationVal = 

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SetSkMesh(*SKMeshAssetPath);

	if (SetSkMesh.Succeeded())
		GetMesh()->SetSkeletalMesh(SetSkMesh.Object);

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

	OnAttackProcessDelegate2Dragon.AddDynamic(this, &AEnemyDragon::AttackProcess);
}

void AEnemyDragon::AttackProcess()
{
	// 공격 판정 함수 호출
	Super::AttackProcess();
}

void AEnemyDragon::Hit()
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

void AEnemyDragon::Attack()
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

