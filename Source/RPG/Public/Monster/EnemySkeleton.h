// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "EnemySkeleton.generated.h"

/**
 *
 */
UCLASS()
class RPG_API AEnemySkeleton : public AEnemyBase
{
	GENERATED_BODY()
public:
	AEnemySkeleton();

	UPROPERTY()
	class UAnimMontage* AnimMontageSpawn;

	FString AnimAssetSpawnPath;

	virtual void BeginPlay()override;
	virtual void Hit()override;
	virtual void AttackProcess()override;
};
