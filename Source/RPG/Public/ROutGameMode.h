// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RGameModeBase.h"
#include "ROutGameMode.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API AROutGameMode : public ARGameModeBase {
	GENERATED_BODY()
	
public:
	AROutGameMode();

	virtual void BeginPlay() override;
};
