// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RPG.h"
#include "Engine/GameInstance.h"
#include "RGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FPreWorldData {
	GENERATED_BODY()

public:

	FORCEINLINE void Reset(FString NewSlotName, FString NewUserName, float NewPlayTime,
		TSubclassOf<class ARPGCharacter> NewCharacterClass, FString NewLevelName, FVector NewLocation) {
		SlotName = NewSlotName;
		UserName = NewUserName;
		PlayTime = NewPlayTime;
		CharacterClassToSpawn = NewCharacterClass;
		SavedLevelName = NewLevelName;
		SavedLocation = NewLocation;
	}


	FORCEINLINE void Reset(const FPreWorldData& OtherPreWorldData) {
		Reset(OtherPreWorldData.SlotName, OtherPreWorldData.UserName,
			OtherPreWorldData.PlayTime, OtherPreWorldData.CharacterClassToSpawn,
			OtherPreWorldData.SavedLevelName, OtherPreWorldData.SavedLocation);
	}

	/* Setter for initial data */
	FORCEINLINE void SetSlotName(FString NewSlotName) { SlotName = NewSlotName; }

	/* Getter for initial data */
	FORCEINLINE FString GetSlotName() const { return SlotName; }
	FORCEINLINE FString GetUserName() const { return UserName; }
	FORCEINLINE float GetPlayTime() const { return PlayTime; }
	FORCEINLINE TSubclassOf<class ARPGCharacter> GetCharacterClassToSpawn() const { return CharacterClassToSpawn; }
	FORCEINLINE FString GetSavedLevelName() const { return SavedLevelName; }
	FORCEINLINE FVector GetSavedLocation() const { return SavedLocation; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Save)
	FString SlotName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Save)
	FString UserName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Save)
	float PlayTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Save)
	TSubclassOf<class ARPGCharacter> CharacterClassToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Save)
	FString SavedLevelName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Save)
	FVector SavedLocation;
};

/**
 * 
 */
UCLASS()
class RPG_API URGameInstance : public UGameInstance {
	GENERATED_BODY()
	
public:
	URGameInstance();

	virtual void Init() override;
	
	/* For loading scene */
	UFUNCTION()
	virtual void BeginLoadingScreen(const FString& MapName);
	UFUNCTION()
	virtual void EndLoadingScreen(UWorld* InLoadedWorld);

	UFUNCTION(BlueprintCallable, Category = Save)
	FPreWorldData& GetPreWorldData() { return PreWorldData; }

	UFUNCTION(BlueprintCallable, Category = Save)
	void InitialSet(FString NewSlotName, FString NewUserName, float NewPlayTime,
		TSubclassOf<class ARPGCharacter> NewCharacterClass, FString NewLevelName, FVector NewLocation) {
		PreWorldData.Reset(NewSlotName, NewUserName, NewPlayTime, NewCharacterClass, NewLevelName, NewLocation);
	}

private:
	UPROPERTY()
	FPreWorldData PreWorldData;
};
