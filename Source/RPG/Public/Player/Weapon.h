// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class RPG_API AWeapon : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	class ARPGCharacter* Temp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

public:	
	AWeapon();

	UFUNCTION()
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackPower = 0.0f;

	UPROPERTY()
	TArray<class AEnemyBase*> Enemy;

	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return Mesh; }
};
