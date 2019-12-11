// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RPG.h"
#include "GameFramework/HUD.h"
#include "RHUDBase.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API ARHUDBase : public AHUD {
	GENERATED_BODY()
	
public:
	ARHUDBase();

	UFUNCTION(BlueprintCallable)
	void ChangeWidget(TSubclassOf<class UUserWidget> NewWidgetClass);
	UFUNCTION(BlueprintCallable)
	class UUserWidget* AddWidget(TSubclassOf<class UUserWidget> NewWidgetClass);
	UFUNCTION(BlueprintCallable)
	void AttachWidget(class UUserWidget* WidgetToAttach);
	UFUNCTION(BlueprintCallable)
	void RemoveWidgetFromTop();
	UFUNCTION(BlueprintCallable)
	void Clear();

	UFUNCTION(BlueprintCallable)
	void SetUIInputMode(class UUserWidget* WidgetToFocus);
	UFUNCTION(BlueprintCallable)
	void SetGameAndUIInputMode();
	UFUNCTION(BlueprintCallable)
	void SetGameInputMode();

protected:
	virtual void BeginPlay() override;



protected:
	UPROPERTY()
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY()
	TArray<class UUserWidget*> CurrentWidgets;

	UPROPERTY()
	class ARPlayerControllerBase* CurrentPC;
};
