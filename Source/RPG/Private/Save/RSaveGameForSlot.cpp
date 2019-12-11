// Fill out your copyright notice in the Description page of Project Settings.


#include "RSaveGameForSlot.h"
#include "RPGCharacter.h"

FString URSaveGameForSlot::ConvertPlayTime() const {
	FString Sec = FString::FromInt((static_cast<int32>(PreWorldData.GetPlayTime())) % 60);
	FString Min = FString::FromInt((static_cast<int32>(PreWorldData.GetPlayTime()) / 60) % 60);
	FString Hour = FString::FromInt((static_cast<int32>(PreWorldData.GetPlayTime()) / 60) / 60);

	return Hour + " : " + Min + " : " + Sec;
}