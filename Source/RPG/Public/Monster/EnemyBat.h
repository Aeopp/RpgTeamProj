// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "EnemyBat.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackProcessDelegate2Bat);

/**
 *
 */
UCLASS()
class RPG_API AEnemyBat : public AEnemyBase
{
	GENERATED_BODY()
public:
	AEnemyBat();
	UPROPERTY()
	class UAnimMontage* AnimMontageAttack2;
	UPROPERTY()
	class UAnimMontage* AnimMontageHit;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = CustomDelegate)
	FOnAttackProcessDelegate2Bat OnAttackProcessDelegate2Bat;

	FString AnimAssetAttack2Path;
	FString AnimAssetHitPath;

	virtual void Attack()override;
	virtual void AttackProcess()override;
	virtual void Hit()override;
};

