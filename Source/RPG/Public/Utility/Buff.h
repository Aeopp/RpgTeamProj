// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Buff.generated.h"

//DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(BuffCheck, UBuff, OnBuffCheck, FString, BName);

USTRUCT(BlueprintType)
struct FBuff
{
	GENERATED_BODY()

	//BuffCheck OnBuffCheck;

	UPROPERTY()
	FString Name;

	UPROPERTY()
	float Buff;

	UPROPERTY()
	float Time;

private:
	void Drop()
	{
		//OnBuffCheck.Broadcast(this, Name);
	}
};
