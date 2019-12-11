// Fill out your copyright notice in the Description page of Project Settings.


#include "RHUDBase.h"
#include "RPlayerControllerBase.h"

#include "ConstructorHelpers.h"
#include "UserWidget.h"

ARHUDBase::ARHUDBase() {

}

void ARHUDBase::BeginPlay() {
	Super::BeginPlay();

	/* Initialize begin */
	CurrentPC = Cast<ARPlayerControllerBase>(GetOwningPlayerController());

	if (HUDWidgetClass) {
		ChangeWidget(HUDWidgetClass);
	}
	/* Initialize end */
}

void ARHUDBase::ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass) {
	check(NewWidgetClass != nullptr);

	/* If there are any widgets now, remove them */
	Clear();

	/* Add new one */
	CurrentWidgets.Empty();
	CurrentWidgets.Push(CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass));
	if (CurrentWidgets.Num()) {
		CurrentWidgets.Top()->AddToViewport(CurrentWidgets.Num());
	}
}

UUserWidget* ARHUDBase::AddWidget(TSubclassOf<UUserWidget> NewWidgetClass) {
	check(NewWidgetClass != nullptr);
	for (const auto& Widget : CurrentWidgets) {
		if (Widget->GetClass() == NewWidgetClass) {
			return nullptr;
		}
	}

	UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
	CurrentWidgets.Push(NewWidget);
	NewWidget->AddToViewport(CurrentWidgets.Num());

	return NewWidget;
}

void ARHUDBase::AttachWidget(class UUserWidget* WidgetToAttach) {
	if (WidgetToAttach) {
		CurrentWidgets.AddUnique(WidgetToAttach);
		WidgetToAttach->AddToViewport(CurrentWidgets.Num());
	}
}

void ARHUDBase::RemoveWidgetFromTop() {
	UUserWidget* WidgetToRemove = CurrentWidgets.Top();
	WidgetToRemove->RemoveFromParent();
	CurrentWidgets.Pop();

	if (CurrentWidgets.Num()) {
		SetUIInputMode(CurrentWidgets.Top());
	}
}

void ARHUDBase::Clear() {
	if (CurrentWidgets.Num()) {
		for (int32 i = 0; i < CurrentWidgets.Num(); ++i) {
			RemoveWidgetFromTop();
		}
	}
}

void ARHUDBase::SetUIInputMode(UUserWidget* WidgetToFocus) {
	if (WidgetToFocus) {
		WidgetToFocus->SetIsEnabled(true);

		FInputModeUIOnly UIInputMode;
		UIInputMode.SetWidgetToFocus(WidgetToFocus->GetCachedWidget());
		if (CurrentPC) {
			CurrentPC->SetInputMode(UIInputMode);
		}
	}
}

void ARHUDBase::SetGameAndUIInputMode() {
	FInputModeGameAndUI GameAndUIInputMode;
	//GameAndUIInputMode
	if (CurrentPC) {
		CurrentPC->SetInputMode(GameAndUIInputMode);
	}
}

void ARHUDBase::SetGameInputMode() {
	FInputModeGameOnly GameInputMode;
	GameInputMode.SetConsumeCaptureMouseDown(false);
	if (CurrentPC) {
		CurrentPC->SetInputMode(GameInputMode);
	}
}