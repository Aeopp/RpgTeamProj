// Fill out your copyright notice in the Description page of Project Settings.


#include "ROutGameHUD.h"
#include "ROutGamePlayerController.h"

#include "ConstructorHelpers.h"
#include "UserWidget.h"

AROutGameHUD::AROutGameHUD() {
	/* Set MainWidget Class */
	static ConstructorHelpers::FClassFinder<UUserWidget> MainWidget(TEXT("WidgetBlueprint'/Game/UI/OutGameWidgets/OutGameMain_BP.OutGameMain_BP_C'"));
	if (MainWidget.Succeeded()) {
		HUDWidgetClass = MainWidget.Class;
	}
}

void AROutGameHUD::BeginPlay() {
	Super::BeginPlay();

	/* Initialize begin */

	/* Initialize end */
}