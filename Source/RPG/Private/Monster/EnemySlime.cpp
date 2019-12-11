// Fill out your copyright notice in the Description page of Project Settings.
#include "EnemySlime.h"

#include "ConstructorHelpers.h"
#include "Components\SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components\CapsuleComponent.h"
#include "Animation/AnimBlueprint.h"

AEnemySlime::AEnemySlime() :Super()
{
	SKMeshAssetPath = TEXT("/Game/Resources/Monsters/Slime/Slime.Slime");
	AnimBPAssetPath = TEXT("/Game/Resources/Monsters/Slime/AnimBP_EnemySlime.AnimBP_EnemySlime");
	AnimAssetDeathPath = TEXT("AnimMontage'/Game/Resources/Monsters/Slime/Slime_Anim_Armature_Slime_Death_Montage.Slime_Anim_Armature_Slime_Death_Montage'");
	AnimAssetAttackPath = TEXT("AnimMontage'/Game/Resources/Monsters/Slime/Slime_Anim_Armature_Slime_Attack_Montage.Slime_Anim_Armature_Slime_Attack_Montage'");
	DeadBodyClassPath = TEXT("Blueprint'/Game/Resources/Monsters/Slime/DeadBodySlime.DeadBodySlime_C'");


	CurrentStat.Attack = 11.f;
	CurrentStat.AttackDistance = 150.f;
	CurrentStat.AttackRadius = 77.f;
	CurrentStat.Defense = 0.f;
	CurrentStat.HP = 100.f;

	GetCharacterMovement()->MaxWalkSpeed  = CurrentStat.Speed  = 250.f;
	GetCapsuleComponent()->InitCapsuleSize(90.f, 45.f);
	GetMesh()->SetRelativeScale3D(FVector{ 50.f,50.f,50.f });
	GetMesh()->SetRelativeLocation(FVector{ 20.f,0.f,-80.f });
	GetMesh()->SetRelativeRotation(FRotator::ZeroRotator);

	bDebugSearchSphereDraw = false;

	AIData.MinTrackingRotationVal = 4.f;
	AIData.MaxTrackingRotationVal = 6.f;
	
	AIData.TrackingRotationVal = FMath::RandRange(AIData.MinTrackingRotationVal,AIData.MaxTrackingRotationVal);
	
	AIData.DetectLocationRadius = 5000.f;
	AIData.DetectSoundsRadius = 250.f;
	AIData.CanAttackRange = 300.f;

	AIData.FindPatrolLocationRadius = 5000.0f;

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

	static auto SetDeath = ConstructorHelpers::FObjectFinder<UAnimMontage>(*AnimAssetDeathPath);
	if (SetDeath.Succeeded())
	{
		AnimMontageDeath = SetDeath.Object;
	}

	static auto SetAttack = ConstructorHelpers::FObjectFinder<UAnimMontage>(*AnimAssetAttackPath);
	if (SetAttack.Succeeded())
	{
		AnimMontageAttack = SetAttack.Object;
	}
}
void AEnemySlime::AttackProcess()
{
	// 공격 판정 함수 호출
	Super::AttackProcess();
}

void AEnemySlime::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemySlime::Hit()
{
	Super::Hit();
}



