// Fill out your copyright notice in the Description page of Project Settings.


#include "RInGameMode.h"
#include "RInGamePlayerController.h"
#include "RInGameHUD.h"
#include "RSaveGame.h"
#include "RSaveGameForSlot.h"
#include "RGameInstance.h"
#include "RPGCharacter.h"

#include "ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"

ARInGameMode::ARInGameMode() {

	/* Temporary */
	static ConstructorHelpers::FClassFinder<ARPGCharacter> CharacterClass(TEXT("Blueprint'/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter.ThirdPersonCharacter_C'"));
	if (CharacterClass.Succeeded()) {
		DefaultPawnClass = CharacterClass.Class;
	}
	/* Temp end */

	PlayerControllerClass = ARInGamePlayerController::StaticClass();
	HUDClass = ARInGameHUD::StaticClass();
	PlayerStateClass = ARPlayerState::StaticClass();

	StartTime = UKismetMathLibrary::Now();
}

void ARInGameMode::BeginPlay() {
	Super::BeginPlay();

	if (GI) {
		FString SlotName = GI->GetPreWorldData().GetSlotName();
		if (SlotName == TEXT("NewGame")) {
			SetPreWorldData();
			SetPostWorldData();
		}
		else {
			Load(SlotName);
		}
	}

	OnDestroyed.AddDynamic(this, &ARInGameMode::OnDestroy);
}

void ARInGameMode::OnDestroy(AActor* DestroyedActor) {
	if (GI) {
		GI->GetPreWorldData().PlayTime += (UKismetMathLibrary::Now() - StartTime).GetTotalSeconds();
	}
}


bool ARInGameMode::Save(const FString& SlotName, const FString& LevelToOpen) {
	/* SaveGameForSlot에 데이터 갱신 후 저장 */
	URSaveGameForSlot* SaveGameForSlot = Cast<URSaveGameForSlot>(UGameplayStatics::CreateSaveGameObject(URSaveGameForSlot::StaticClass()));
	if (SaveGameForSlot) {
		ARPGCharacter* CurrentCharacter = Cast<ARPGCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
		if (GI && CurrentCharacter) {
			/* Reset Play Time */
			GI->GetPreWorldData().PlayTime += (UKismetMathLibrary::Now() - StartTime).GetTotalSeconds();
			StartTime = UKismetMathLibrary::Now();

			if (LevelToOpen != TEXT("Saved")) {
				SaveGameForSlot->GetPreWorldData().Reset(SlotName,
					GI->GetPreWorldData().GetUserName(), GI->GetPreWorldData().GetPlayTime(),
					CurrentCharacter->GetClass(), LevelToOpen, CurrentCharacter->GetActorLocation());
			}
			else {
				SaveGameForSlot->GetPreWorldData().Reset(SlotName,
					GI->GetPreWorldData().GetUserName(), GI->GetPreWorldData().GetPlayTime(),
					CurrentCharacter->GetClass(), GetWorld()->GetName(), CurrentCharacter->GetActorLocation());
			}

			/* Reset GI PreWorldData */
			GI->GetPreWorldData().Reset(SaveGameForSlot->GetPreWorldData());
		}

		if (UGameplayStatics::SaveGameToSlot(SaveGameForSlot, SlotName + TEXT(" for slot"), 0)) {
			/* SaveGame에 데이터 갱신 후 저장 */
			if (!SaveGame) {
				SaveGame = Cast<URSaveGame>(UGameplayStatics::CreateSaveGameObject(URSaveGame::StaticClass()));
			}
			if (SaveGame) {
				SaveGame->SetAll(GetWorld());
			}
			return UGameplayStatics::SaveGameToSlot(SaveGame, SlotName, 0);
		}
	}

	return false;
}

bool ARInGameMode::Load(const FString& SlotName) {
	if (Super::Load(SlotName)) {
		if (GI) {
			/* Set PreWorld Data */
			SetPreWorldData();

			SaveGame = Cast<URSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
			if (SaveGame) {
				/* Set PostWorld Data */
				SetPostWorldData(SaveGame);
			}
			return false;
		}
		return false;
	}
	return false;
}

void ARInGameMode::SetPreWorldData() {
	UWorld* World = GetWorld();
	if (World) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ARPGCharacter* NewCharacter = World->SpawnActor<ARPGCharacter>(GI->GetPreWorldData().GetCharacterClassToSpawn(), GI->GetPreWorldData().GetSavedLocation(), FRotator::ZeroRotator, SpawnParams);
		if (NewCharacter) {
			ARInGamePlayerController* CurrentPC = Cast<ARInGamePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
			if (CurrentPC) {
				CurrentPC->GetPawn()->Destroy();
				CurrentPC->UnPossess();
				CurrentPC->Possess(NewCharacter);
			}
		}
	}
}

void ARInGameMode::SetPostWorldData(URSaveGame* SaveGameForPostSet) {
	auto CurrentChar = Cast<ARPGCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (CurrentChar) {
		if (SaveGameForPostSet) {
			CurrentChar->Stat = SaveGameForPostSet->SavedStat;
			CurrentChar->Equipment = SaveGameForPostSet->SavedEquipment;
		}
		else {
			FCStat NewStat = { 1, 100, 0, 10000, 10000, 50, 50, 20, 10, 10, 10, 10, 4, ECurState::Normal };
			CurrentChar->Stat = NewStat;
		}
	}
}