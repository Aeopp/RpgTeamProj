// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "EnemySlime.generated.h"

/**
 *
 */
UCLASS()
class RPG_API AEnemySlime : public AEnemyBase
{
	GENERATED_BODY()
public:
	AEnemySlime();

	virtual void BeginPlay()override;
	virtual void Hit()override;
	virtual void AttackProcess()override;
};
