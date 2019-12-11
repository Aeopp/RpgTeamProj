// Fill out your copyright notice in the Description page of Project Settings.
#include "RandomSpawner.h"

#include "ConstructorHelpers.h"
#include "Components\BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ARandomSpawner::ARandomSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
}

// Called when the game starts or when spawned
void ARandomSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARandomSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARandomSpawner::RandomSpawn()
{
	if (auto World = GetWorld())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = nullptr;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		FVector RandomLocation= UKismetMathLibrary::RandomPointInBoundingBox(SpawnVolume->Bounds.Origin, SpawnVolume->Bounds.BoxExtent);
		FRotator RandomRotation = FRotator::ZeroRotator;

		GetWorld()->SpawnActor<AEnemyBase>(SpawnTarget, RandomLocation, RandomRotation, SpawnParams);
	}
}

