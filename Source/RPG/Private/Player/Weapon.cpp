// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/StaticMeshComponent.h"
#include "RPGCharacter.h"
#include "EnemyBase.h"

// Sets default values
AWeapon::AWeapon()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AWeapon::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (Temp) 
	{
		auto Monster = Cast<AEnemyBase>(OtherActor);

		if (Monster) {
			int32 I;
			if (Enemy.Find(Monster, I)) {
				return;
			}
			Enemy.AddUnique(Monster);
			Temp->Attack(Monster);
		}
	}
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	Temp = Cast<ARPGCharacter>(GetOwner());
	OnActorBeginOverlap.AddDynamic(this, &AWeapon::BeginOverlap);
}