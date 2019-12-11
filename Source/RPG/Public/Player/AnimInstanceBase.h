// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstanceBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttackCheck);

UCLASS()
class RPG_API UAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

	
public:
	UAnimInstanceBase();

	UPROPERTY()
	class AWeapon* TWeapon;

	void PlayMontage(UAnimMontage* AnimMontage, float PlayRate = 1.0f);

	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category=CustomDelegate)
	FAttackCheck OnAttackCheck;

	UFUNCTION(BlueprintCallable)
	void SetWeapon(class AWeapon* NewWeapon);

private:
	UFUNCTION()
	void AnimNotify_AttackStart();
	UFUNCTION()
	void AnimNotify_AttackEnd();
	UFUNCTION()
	void AnimNotify_End();
};
