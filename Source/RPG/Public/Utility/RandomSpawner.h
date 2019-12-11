// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "EnemyBase.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomSpawner.generated.h"

UCLASS()
class RPG_API ARandomSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARandomSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, Category = SpawnActorSelect)
	TSubclassOf<class AEnemyBase> SpawnTarget;

	UFUNCTION(BlueprintCallable,Category=RandomSpawn)
	void RandomSpawn();
private:
	class UBoxComponent* SpawnVolume;
	bool bIsSpawnActive = false;
};
