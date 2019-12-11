// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterBase.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TimerManager.h"

//Debug Include End
#include "Global.h"
//............
#include "RPGCharacter.h"


// Sets default values
ACharacterBase::ACharacterBase() : ACharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GetCharacterMovement()->MaxWalkSpeed = CurrentStat.Speed;
}
void ACharacterBase::Attack()
{
	CurState = EState::Attacking;
	FTimerHandle AttackCoolDown;

	// 공격 쿨타임이 끝나면 다시 공격할수있게 상태값 갱신
	GetWorldTimerManager().SetTimer(AttackCoolDown, 
	FTimerDelegate::CreateLambda([this] {CurState = EState::Idle; }), 
	CurrentStat.AttackRatio,false);
}
void ACharacterBase::AttackProcess()
{
	//TArray<FHitResult> HitActors;
	//TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
	//ObjectType.Add(EObjectTypeQuery::ObjectTypeQuery3);
	//TArray<AActor*> Ignore;
	//Ignore.Add(this);
	//FVector Start = GetActorLocation();
	//FVector End = ((UKismetMathLibrary::GetForwardVector(GetActorRotation()) * CurrentStat.AttackDistance) + Start);
	//int32 PrintNumber = 0;

	//if (UKismetSystemLibrary::SphereTraceMultiForObjects(
	//	this, Start, End, CurrentStat.AttackRadius,
	//	ObjectType, false, Ignore, EDrawDebugTrace::ForDuration, OUT HitActors, true
	//))
	//{
	//	for (auto& HitActor : HitActors)
	//	{
	//		if (HitActor.Actor.IsValid())
	//		{
	//			if (ARPGCharacter* Target = Cast<ARPGCharacter>(HitActor.GetActor()))
	//			{
	//				UE_LOG(LogTemp, Warning, TEXT("%s"), *Target->GetName());
	//				FDamageEvent DamageEvent;
	//				FString AttackLog = GetDebugName(this) + TEXT("s Attack !! Damage = ") + FString::SanitizeFloat(this->CurrentStat.Attack);
	//				UE_LOG(LogTemp, Error, TEXT("%s"), *AttackLog);
	//				Target->TakeDamage(this->CurrentStat.Attack, DamageEvent, GetController(), this);
	//				PrintNumber++;
	//			}
	//		}
	//	}
	//}
	//UE_LOG(LogTemp, Error, TEXT("%d"), PrintNumber);
	TArray<FHitResult> OutHits;
	const FVector Start = GetActorLocation();
	const FVector End = Start + ( GetActorForwardVector() * this->CurrentStat.AttackDistance);
	const FQuat Rot = FQuat::Identity;
	const FCollisionObjectQueryParams ObjectQueryParams = FCollisionObjectQueryParams::DefaultObjectQueryParam;
	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(this->CurrentStat.AttackRadius);
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	int32 PrintNumber = 0;

	if (GetWorld()->SweepMultiByObjectType(OutHits, Start, End, Rot, ObjectQueryParams, CollisionShape, CollisionQueryParams))
	{
		for (auto& Targets : OutHits)
		{
			if (auto* PlayerCharater = Cast<ARPGCharacter>(Targets.GetActor()))
			{
				UE_LOG(LogTemp, Warning, TEXT("%s"), *PlayerCharater->GetName());
				FDamageEvent DamageEvent;
				FString AttackLog = GetDebugName(this) + TEXT("s Attack !! Damage = ") + FString::SanitizeFloat(this->CurrentStat.Attack);
				UE_LOG(LogTemp, Error, TEXT("%s"), *AttackLog);
				PlayerCharater->TakeDamage(this->CurrentStat.Attack, DamageEvent, GetController(), this);
				PrintNumber++;
			}
		}
	}
	
	UE_LOG(LogTemp, Error, TEXT("%d"), PrintNumber);
}
void ACharacterBase::Hit()
{
	FString HitActorLog = GetDebugName(this) + TEXT("s Hited !! ");
	DebugScreenMessage(HitActorLog, 3.f, FColor::Red);
}
void ACharacterBase::Death()
{
	SetLifeSpan(5.f);
	bCanBeDamaged = false;
	CurState = EState::Deathed;
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	OnTakeAnyDamage.AddDynamic(this, &ACharacterBase::RecieveAnyDamage);
	OnAttackProcessDelegate.AddDynamic(this, &ACharacterBase::AttackProcess);
	OnDeathDelegate.AddDynamic(this, &ACharacterBase::Death);
}

void ACharacterBase::RecieveAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Hit();
	CurrentStat.HP -= Damage;

	if(CurrentStat.HP<=0)
	{
		Death();
		FString DeathedActorLog = TEXT("Deathed Actor DebugName = ")  + this->GetDebugName(this) + TEXT("Deathed Actor Name") + this->GetName(); 
		UE_LOG(LogTemp, Error, TEXT("%s"),*DeathedActorLog);
	}
}



