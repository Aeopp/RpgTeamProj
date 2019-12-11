// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstanceBase.h"
#include "RPGCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Weapon.h"
#include "Components/StaticMeshComponent.h"



UAnimInstanceBase::UAnimInstanceBase()
{
	TWeapon = CreateDefaultSubobject<AWeapon>(TEXT("Weapon"));
}

void UAnimInstanceBase::PlayMontage(UAnimMontage* AnimMontage, float PlayRate)
{
	if (!Montage_IsPlaying(AnimMontage))
	{
		Montage_Play(AnimMontage, PlayRate);
	}
}

void UAnimInstanceBase::AnimNotify_AttackStart()
{
	UE_LOG(LogTemp, Error, TEXT("AnimNotify_AttackStart"));
	TWeapon->GetMesh()->SetCollisionProfileName(TEXT("OverlapAll"));
}

void UAnimInstanceBase::AnimNotify_AttackEnd()
{
	UE_LOG(LogTemp, Error, TEXT("AnimNotify_AttackEnd"));
	TWeapon->GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	TWeapon->Enemy.Empty();
}

void UAnimInstanceBase::AnimNotify_End()
{
	FDetachmentTransformRules DetachRules = { EDetachmentRule::KeepRelative,EDetachmentRule::KeepRelative,EDetachmentRule::KeepRelative,true };
	FAttachmentTransformRules AttachRules = { EAttachmentRule::KeepRelative,EAttachmentRule::KeepRelative,EAttachmentRule::KeepRelative,false };
	TWeapon->DetachFromActor(DetachRules);
	TWeapon->AttachToComponent(UGameplayStatics::GetPlayerCharacter(this, 0)->GetMesh(), AttachRules, TEXT("FWeapon"));
	TWeapon->SetActorLocation(UGameplayStatics::GetPlayerCharacter(this, 0)->GetMesh()->GetSocketLocation(TEXT("FWeapon")));
	TWeapon->SetActorLocation(TWeapon->GetMesh()->GetSocketLocation(TEXT("back")));
}

void UAnimInstanceBase::SetWeapon(class AWeapon* NewWeapon) {
	TWeapon = NewWeapon;
}