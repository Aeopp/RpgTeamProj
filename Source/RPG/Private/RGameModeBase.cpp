// Fill out your copyright notice in the Description page of Project Settings.


#include "RGameModeBase.h"
#include "RGameInstance.h"
#include "RSaveGameForSlot.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ARGameModeBase::ARGameModeBase() {

}

void ARGameModeBase::BeginPlay() {
	Super::BeginPlay();

	GI = Cast<URGameInstance>(GetGameInstance());
}

bool ARGameModeBase::Load(const FString& SlotName) {
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0)) {
		URSaveGameForSlot* SaveGameForSlot = Cast<URSaveGameForSlot>(UGameplayStatics::LoadGameFromSlot(SlotName + TEXT(" for slot"), 0));

		if (SaveGameForSlot) {
			/* SaveGameForSlot에서 불러온 데이터 갱신 */
			if (GI) {
				GI->GetPreWorldData().Reset(SaveGameForSlot->GetPreWorldData());

				FString LevelName = GI->GetPreWorldData().GetSavedLevelName();
				if (LevelName != UGameplayStatics::GetCurrentLevelName(this)) {
					UGameplayStatics::OpenLevel(this, FName(*LevelName));
				}
				else {
					StartTime = UKismetMathLibrary::Now();
				}
			}
		}
		return true;
	}
	else {
		return false;
	}
}