// Fill out your copyright notice in the Description page of Project Settings.


#include "Global.h"

void DebugScreenMessage(const FString& PrintStr, const float PrintTime, FColor Color)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, PrintTime, Color, *PrintStr, false);
}

