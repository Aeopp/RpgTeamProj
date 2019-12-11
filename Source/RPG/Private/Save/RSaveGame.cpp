// Fill out your copyright notice in the Description page of Project Settings.


#include "RSaveGame.h"
#include "RInGamePlayerController.h"
#include "RPlayerState.h"

#include "Kismet/GameplayStatics.h"

void URSaveGame::SetAll(UObject* Object) {
	auto CurrentPC = Cast<ARInGamePlayerController>(UGameplayStatics::GetPlayerController(Object, 0));
	if (CurrentPC) {
		auto CurrentPS = CurrentPC->GetPlayerState<ARPlayerState>();
		if (CurrentPS) {
			CurrentPS->SetAll();
			SavedStat = CurrentPS->Stat;
			SavedEquipment = CurrentPS->Equipment;
		}
	}
}