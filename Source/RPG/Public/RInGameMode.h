// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RGameModeBase.h"
#include "RInGameMode.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API ARInGameMode : public ARGameModeBase {
	GENERATED_BODY()
	
public:
	ARInGameMode();

	UFUNCTION(BlueprintCallable)
	bool Save(const FString& SlotName, const FString& LevelToOpen = TEXT("Saved"));

	virtual bool Load(const FString& SlotName) override;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnDestroy(AActor* DestroyedActor);

	void SetPreWorldData();
	void SetPostWorldData(class URSaveGame* SaveGame = nullptr);

private:
	UPROPERTY()
	class URSaveGame* SaveGame;
};
