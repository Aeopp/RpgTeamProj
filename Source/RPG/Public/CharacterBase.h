// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/CharacterMovementComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackProcessDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathDelegate);

UENUM(BlueprintType,Blueprintable)
enum class EState : uint8
{
	Attacking,
	Deathed,
	Idle,
};

USTRUCT(BlueprintType,Blueprintable)
struct FCommonStat
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HP = 100.00;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EXP = 11.11f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRatio = 2.55f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Attack = 77.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Defense = 9.99f;

	// 공격 판정 사거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackDistance = 200.f;

	// 공격 판정 구체를 사용할 때의 판정 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRadius = 30.f;
};

UCLASS()
class RPG_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	ACharacterBase();
protected:
	// Called when the game starts or when spawned
public:	
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = CustomDelegate)
	FOnAttackProcessDelegate OnAttackProcessDelegate;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = CustomDelegate)
	FOnDeathDelegate OnDeathDelegate;
	// MyCustom Begin ... 
	UFUNCTION()
	virtual void Hit();
	// 공격 물리처리 함수
	UFUNCTION()
	virtual void Attack();
	UFUNCTION()
	virtual void AttackProcess();
	UFUNCTION(BlueprintCallable, Category = Test)
	virtual void Death();

	virtual void BeginPlay()override;

	UPROPERTY(EditAnywhere, Category = State)
	EState CurState = EState::Idle;
	UPROPERTY(EditAnywhere, Category = Stat)
	FCommonStat CurrentStat;
	
	FORCEINLINE void Running()
	{GetCharacterMovement()->MaxWalkSpeed = CurrentStat.Speed * 2;}

	FORCEINLINE void StopRunning()
	{GetCharacterMovement()->MaxWalkSpeed = CurrentStat.Speed;}

	UFUNCTION()
	void RecieveAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};

