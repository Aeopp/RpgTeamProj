// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "RPlayerState.h"
#include "GameFramework/Character.h"
#include "RPGCharacter.generated.h"

UCLASS(config=Game)
class ARPGCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY()
	class UAnimInstanceBase* Anim;

public:
	ARPGCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/* Toggle Menu Widget */
	UFUNCTION(BlueprintCallable)
	void ToggleMenuInGame();

	UFUNCTION(BlueprintCallable)
	void ToggleCharacterStateMenu();

	UFUNCTION()
	void Attack(AActor* Actor);

protected:

	UFUNCTION(BlueprintCallable)
	void Attack_AnimPlay();
	void Running();
	void StopRunning();
	void Stop();
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Death();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void RecieveAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	//void OnResetVR();
	//void TurnAtRate(float Rate);
	//void LookUpAtRate(float Rate);
	//void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	//void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

private:
	UPROPERTY()
	float temp = 0.0f;
	UPROPERTY()
	bool StopAttack = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon", Meta = (AllowPrivateAccess = true))
	class AWeapon* Weapon;

	//UPROPERTY()
	//TArray<> BuffArray;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* StopAttackMontage;

public:
	UFUNCTION(BlueprintCallable)
	float GetDamage();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCStat Stat;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCEquipment Equipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Attacking = false;


	UFUNCTION(BlueprintCallable)
	void SetWeapon(class AWeapon* NewWeapon);

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
	UPROPERTY()
	class UUserWidget* MenuInGame;
	UPROPERTY()
	class UUserWidget* CharacterStateMenu;

	bool bMenuInGame = false;
	bool bCharacterStateMenu = false;

public:
	UPROPERTY()
	TSubclassOf<class UUserWidget>Inventory;
	UPROPERTY()
	class UUserWidget* InvenWidget;

};