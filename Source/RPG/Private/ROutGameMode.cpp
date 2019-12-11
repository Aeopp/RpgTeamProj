// Fill out your copyright notice in the Description page of Project Settings.


#include "ROutGameMode.h"
#include "ROutGamePlayerController.h"
#include "ROutGameHUD.h"

AROutGameMode::AROutGameMode() {
	PlayerControllerClass = AROutGamePlayerController::StaticClass();
	HUDClass = AROutGameHUD::StaticClass();
}

void AROutGameMode::BeginPlay() {
	Super::BeginPlay();
}