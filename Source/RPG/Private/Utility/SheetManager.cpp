// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SheetManager.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "Runtime/Json/Public/Serialization/JsonReader.h"
#include "Runtime/Json/Public/Dom/JsonObject.h"
#include "Runtime/Json/Public/Serialization/JsonSerializer.h"
#include "Runtime/Json/Public/Dom/JsonValue.h"
#include "Public/Http.h"




// Sets default values
ASheetManager::ASheetManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	for (uint8 SheetType = (uint8)ESheetType::Begin + 1; SheetType < (uint8)ESheetType::End; ++SheetType)
	{
		HttpCallSheets.Enqueue(static_cast<ESheetType>(SheetType));
	}
}

// Called when the game starts or when spawned
void ASheetManager::BeginPlay()
{
	Super::BeginPlay();
	Http = &FHttpModule::Get();
	UE_LOG(LogTemp, Error, TEXT(" Http Get "));


	ESheetType ParamSheetType;
	if (HttpCallSheets.Dequeue(ParamSheetType))
	{
		HttpCall(ParamSheetType);
	}
}
// Called every frame
void ASheetManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASheetManager::HttpCall(const ESheetType& SheetType)
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();

	CurrentSheetType = SheetType;

	const FString URL = FString::Printf
	(TEXT("http://spreadsheets.google.com/a/google.com/tq?key=%s&gid=%s"),
		*Sheet::GetSheetKey(), *Sheet::GetTypeID(CurrentSheetType));

	Request->OnProcessRequestComplete().BindUObject(this, &ASheetManager::OnResponseReceived);
	Request->SetURL(URL);
	Request->SetVerb(TEXT("GET"));
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();

	UE_LOG(LogTemp, Error, TEXT("Sheet URL Print : %s"), *URL);
}

void ASheetManager::OnResponseReceived
(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Error, TEXT("%s"), bWasSuccessful ? TEXT("Success") : TEXT("FALSE"));

	if (!Response.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Not Valid"));
	}
	else if (!bWasSuccessful)
	{
		UE_LOG(LogTemp, Error, TEXT("OnResponseReceived Fail"));
	}
	else if (EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		// valid response
		FString ParsTarget = Response->GetContentAsString();

		UE_LOG(LogTemp, Error, TEXT("%s"), *ParsTarget);

		// 이제 파싱 시작
		FString JsonData = Response->GetContentAsString();

		int32 First, Last;

		JsonData.FindChar('(', OUT First);
		JsonData.FindLastChar(')', OUT Last);
		++First;

		FString Data = JsonData.Mid(First, Last - First);
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(Data);
		TSharedPtr<FJsonObject> Json = MakeShareable(new FJsonObject());

		if (FJsonSerializer::Deserialize(Reader, OUT Json) == true &&
			Json.IsValid() == true)
		{
			auto& Object = Json->GetObjectField(TEXT("table"));

			auto& Arr = Object->GetArrayField(TEXT("rows"));

			// 파싱된 맵을 돌려줄것임
			const auto& Insert = Sheet::MakeSheetTable(Arr, CurrentSheetType);

			//	Sheets.Add(CurrentSheetType, Insert);
			Sheets.Add(CurrentSheetType, Insert);
		}
		ESheetType ParamSheetType;
		if (HttpCallSheets.Dequeue(ParamSheetType))
		{
			HttpCall(ParamSheetType);
		}
	}

	UE_LOG(LogTemp, Error, TEXT("OnResponseReceived End !! "));
}

void ASheetManager::SheetDataPrint() const
{
	for (auto& PrintMap : Sheets)
	{
		if (GEngine)
		{
			const UEnum* EnumPrint = FindObject<UEnum>
				(ANY_PACKAGE, TEXT("ESheetType"), true);

			if (EnumPrint)
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow,
					*EnumPrint->GetDisplayNameTextByValue((int64)PrintMap.Key).ToString(), false);
			}
		}

		for (auto& Printing : PrintMap.Value)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, (TEXT("Key : %s"), *Printing.Key), false);

			Printing.Value->MemberPrint();
		}
	}
}

ASheetManager::~ASheetManager()
{

}




