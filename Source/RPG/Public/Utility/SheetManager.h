// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Global.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Queue.h"
#include "Templates/SharedPointer.h"

#include "SheetManager.generated.h"

UCLASS()
class RPG_API ASheetManager : public AActor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ASheetManager();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	class FHttpModule* Http;

	void OnResponseReceived
	(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// TMap<ESheetType, TMap<FString,FSheetBase*>> Sheets;
	TMap<ESheetType, TMap<FString, TSharedPtr<FSheetBase>>> Sheets;

	TQueue<ESheetType> HttpCallSheets;

	void HttpCall(const ESheetType& SheetType);

	ESheetType CurrentSheetType;

	UFUNCTION(BlueprintCallable, Category = TestCode)
	void SheetDataPrint()const;

	~ASheetManager();
};
