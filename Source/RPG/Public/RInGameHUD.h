// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RHUDBase.h"
#include "RInGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API ARInGameHUD : public ARHUDBase {
	GENERATED_BODY()
	
public:
	ARInGameHUD();

	UFUNCTION(BlueprintCallable)
	void RemoveWidget(class UUserWidget* WidgetToRemove);

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	TSubclassOf<class UUserWidget> MainMenuWidgetClass;

	UPROPERTY()
	TSubclassOf<class UUserWidget> CharacterStateWidgetClass;
};
