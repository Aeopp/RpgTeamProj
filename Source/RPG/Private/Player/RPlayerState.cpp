// Fill out your copyright notice in the Description page of Project Settings.


#include "RPlayerState.h"
#include "RPGCharacter.h"

#include "Kismet/GameplayStatics.h"

ARPlayerState::ARPlayerState() {

}

void ARPlayerState::SetAll() {
	SetStat();
	SetEquipment();
}

void ARPlayerState::SetStat() {
	auto Character = Cast<ARPGCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Character) {
		Stat = Character->Stat;
	}
}

void ARPlayerState::SetEquipment() {
	auto Character = Cast<ARPGCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Character) {
		Equipment = Character->Equipment;
	}
}