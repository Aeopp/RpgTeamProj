// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RPG.h"
#include "GameFramework/GameModeBase.h"
#include "RGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API ARGameModeBase : public AGameModeBase {
	GENERATED_BODY()
	
public:
	ARGameModeBase();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual bool Load(const FString& SlotName);

protected:
	UPROPERTY()
	class URGameInstance* GI;

	UPROPERTY()
	FDateTime StartTime;
};
