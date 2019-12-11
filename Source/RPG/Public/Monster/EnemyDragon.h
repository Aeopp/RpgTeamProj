// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "EnemyDragon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackProcessDelegate2Dragon);
/**
 *
 */
UCLASS()
class RPG_API AEnemyDragon : public AEnemyBase
{
	GENERATED_BODY()
public:
	UPROPERTY()
	class UAnimMontage* AnimMontageAttack2;
	UPROPERTY()
	class UAnimMontage* AnimMontageHit;
	AEnemyDragon();
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = CustomDelegate)
	FOnAttackProcessDelegate2Dragon OnAttackProcessDelegate2Dragon;

	FString AnimAssetAttack2Path;
	FString AnimAssetHitPath;

	virtual void Attack()override;
	virtual void AttackProcess()override;
	virtual void Hit()override;
};
