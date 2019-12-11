// Fill out your copyright notice in the Description page of Project Settings.


#include "RInGameHUD.h"

#include "ConstructorHelpers.h"
#include "UserWidget.h"

ARInGameHUD::ARInGameHUD() {
	/* Set MainWidget Class */
	static ConstructorHelpers::FClassFinder<UUserWidget> BaseWidget(TEXT("WidgetBlueprint'/Game/UI/InGameWidgets/InGameBasic_BP.InGameBasic_BP_C'"));
	if (BaseWidget.Succeeded()) {
		HUDWidgetClass = BaseWidget.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuWidget(TEXT("WidgetBlueprint'/Game/UI/InGameWidgets/InGameMain_BP.InGameMain_BP_C'"));
	if (MainMenuWidget.Succeeded()) {
		MainMenuWidgetClass = MainMenuWidget.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> CharacterStateWidget(TEXT("WidgetBlueprint'/Game/UI/InGameWidgets/CharacterState_BP.CharacterState_BP_C'"));
	if (CharacterStateWidget.Succeeded()) {
		CharacterStateWidgetClass = CharacterStateWidget.Class;
	}
}

void ARInGameHUD::BeginPlay() {
	Super::BeginPlay();

	SetGameAndUIInputMode();
}

void ARInGameHUD::RemoveWidget(UUserWidget* WidgetToRemove) {
	if (WidgetToRemove) {
		WidgetToRemove->RemoveFromParent();
		CurrentWidgets.RemoveSingle(WidgetToRemove);
	}
}