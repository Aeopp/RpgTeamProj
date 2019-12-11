// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RPG.h"
#include "GameFramework/PlayerState.h"
#include "RPlayerState.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ECurState : uint8 {
	Normal,

	Poisoned,
	Burned,
	Frozend,
};

/* 'C' means the Character */
USTRUCT(BlueprintType, Blueprintable)
struct FCStat {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	int32 Level;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	float MaxExp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	float Exp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	float MaxHp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	float Hp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	float MaxMp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	float Mp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	float Attack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	int32 Str;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	int32 Dex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	int32 Int;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	int32 Luck;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	int32 StatPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	ECurState CurState;
};

/* 'C' means the Character */
USTRUCT(BlueprintType, Blueprintable)
struct FCEquipment {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equipment)
	float Head;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equipment)
	float Body;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equipment)
	float Foot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equipment)
	float Hand;
};

UCLASS()
class RPG_API ARPlayerState : public APlayerState {
	GENERATED_BODY()

public:
	ARPlayerState();

	UFUNCTION(BlueprintCallable, Category = PlayerState)
	void SetAll();

private:
	void SetStat();
	void SetEquipment();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	FCStat Stat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	FCEquipment Equipment;
};
