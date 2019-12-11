// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RGameInstance.h"
#include "GameFramework/SaveGame.h"
#include "RSaveGameForSlot.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URSaveGameForSlot : public USaveGame {
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Save)
	FString ConvertPlayTime() const;

	UFUNCTION(BlueprintCallable, Category = Save)
	FPreWorldData& GetPreWorldData() { return PreWorldData; }

	UFUNCTION(BlueprintCallable, Category = Save)
	FString GetTextForSlot() { return PreWorldData.GetUserName() + TEXT("  ") + ConvertPlayTime(); }

private:
	UPROPERTY()
	FPreWorldData PreWorldData;
};
