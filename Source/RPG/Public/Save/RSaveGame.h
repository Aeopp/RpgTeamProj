// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RPlayerState.h"

#include "GameFramework/SaveGame.h"
#include "RSaveGame.generated.h"

/**
 * 
 */

UCLASS()
class RPG_API URSaveGame : public USaveGame {
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, Category = Stat)
	void SetAll(UObject* Object);

public:
	UPROPERTY()
	FCStat SavedStat;

	UPROPERTY()
	FCEquipment SavedEquipment;
};
