// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Debug Message 
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
// RemovePlz

#include "Templates/SharedPointer.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Global.generated.h"

// Debug Function 
void DebugScreenMessage(const FString& PrintStr, const float PrintTime, FColor Color);


UENUM(BlueprintType)
enum class ESheetType :uint8
{
	Begin,

	TwoHandSword,
	Config,
	Sword,

	End,
};

USTRUCT(BlueprintType)
struct FSheetBase
{
	GENERATED_BODY()

	using Super = FSheetBase;

	FSheetBase() {};
	FSheetBase(const FSheetBase& Rhs) :MyID(Rhs.MyID), Name(Rhs.Name) {};

	UPROPERTY()
	uint32 MyID;
	UPROPERTY()
	FString Name;

	FORCEINLINE virtual void MemberPrint()const
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, 
			FString::Printf(TEXT("MyName is  : %s \n MyID is : %d"), *Name, MyID), false);
			/*	UE_LOG(LogTemp, Error,TEXT("MyName is  : %s \n MyID is : %s"), *Name, *MyID);*/
		}
	};

	virtual ~FSheetBase() {};
};

USTRUCT(BlueprintType)
struct FConfig : public FSheetBase
{
	GENERATED_BODY()

		UPROPERTY()
		float Version;
	FConfig() :Super() {};
	FConfig(const FConfig& Rhs) :Super(), Version(Rhs.Version) {};

	FORCEINLINE virtual void MemberPrint()const override
	{
		FSheetBase::MemberPrint();

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, (TEXT("  Version  : %s "), FString::SanitizeFloat(Version)), false);
			/*	UE_LOG(LogTemp, Error, TEXT(" Current Version  : %s "), FString::SanitizeFloat(Version));*/
		};
	}
	virtual ~FConfig()override {};
};

USTRUCT(BlueprintType)
struct FTwoHandSword : public FSheetBase
{
	GENERATED_BODY()
		UPROPERTY()
		uint32 Level;
	UPROPERTY()
		float Attack;
	UPROPERTY()
		FString Option;
	UPROPERTY()
		float Range;

	FTwoHandSword() :Super() {};
	FTwoHandSword(const FTwoHandSword& Rhs) :Super(), Level(Rhs.Level), Attack(Rhs.Attack), Option(Rhs.Option), Range(Rhs.Range) {};

	FORCEINLINE virtual void MemberPrint()const override
	{
		FSheetBase::MemberPrint();

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, (TEXT("FTwoHandSword Data : Level : %s Attack  : %s Option : %s  Range : %s "),
				*FString::FromInt(Level), FString::SanitizeFloat(Attack), *Option, *FString::SanitizeFloat(Range)),
				false);
		};
	}

	virtual ~FTwoHandSword()override {};
};

USTRUCT(BlueprintType)
struct FSword :public FSheetBase
{
	GENERATED_BODY()

		UPROPERTY()
		uint32 Level;
	UPROPERTY()
		float Attack;
	UPROPERTY()
		FString Option;
	UPROPERTY()
		float Range;

	FSword() :Super() {};
	FSword(const FSword& Rhs) :Super(), Level(Rhs.Level), Attack(Rhs.Attack), Option(Rhs.Option), Range(Rhs.Range) {};

	FORCEINLINE virtual void MemberPrint()const override
	{
		FSheetBase::MemberPrint();

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, (TEXT("FSword Data : Level : %s Attack  : %s Option : %s  Range : %s "),
				*FString::FromInt(Level), FString::SanitizeFloat(Attack), *Option, *FString::SanitizeFloat(Range)),
				false);
		};
	}

	virtual ~FSword()override {};
};

class Sheet
{
public:
	static FORCEINLINE FString GetTypeID(ESheetType WantTypeID)
	{
		FString ReturnTypeID;

		switch (WantTypeID)
		{
		case ESheetType::TwoHandSword:
			ReturnTypeID = TEXT("0");
			break;
		case ESheetType::Config:
			ReturnTypeID = TEXT("1952188101");
			break;
		case ESheetType::Sword:
			ReturnTypeID = TEXT("1768599225");
			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("Sheet::GetTypeID Paramater(ESheetType) Error"));
			break;
		}
		return ReturnTypeID;
	}

	static FORCEINLINE FString GetSheetKey()
	{
		return TEXT("1JU_KXpkweHvbDBC5yAOz3rQXxhJoj_Gyna5TrDA0yeE");
	}

	static FORCEINLINE FString GetSheetURL()
	{
		return TEXT("http://spreadsheets.google.com/a/google.com/tq?key=%s&gid=%s");
	}

	static FORCEINLINE void MakeSheetByType
	(TMap<FString, TSharedPtr<FSheetBase>>& OutSheet, ESheetType SheetType,
		const TArray<TSharedPtr<FJsonValue>>& ParserTarget)
	{
		switch (SheetType)
		{
		case ESheetType::TwoHandSword:
		{
			uint32 IDNumber = 0;
			for (const auto& CurrentObj : ParserTarget)
			{
				uint8 Index = 0;

				auto TargetData = new FTwoHandSword;

				auto& Array = CurrentObj->AsObject()->GetArrayField(TEXT("c"));

				TargetData->MyID = IDNumber++;
				TargetData->Name = Array[Index++]->AsObject()->GetStringField(TEXT("v"));
				TargetData->Level = Array[Index++]->AsObject()->GetIntegerField(TEXT("v"));
				TargetData->Attack = Array[Index++]->AsObject()->GetNumberField(TEXT("v"));
				TargetData->Option = Array[Index++]->AsObject()->GetStringField(TEXT("v"));
				TargetData->Range = Array[Index++]->AsObject()->GetNumberField(TEXT("v"));

				OutSheet.Add(TargetData->Name, MakeShareable<FTwoHandSword>(TargetData));
			}
			break;
		}
		case ESheetType::Config:
		{
			uint32 IDNumber = 0;
			for (const auto& CurrentObj : ParserTarget)
			{
				uint8 Index = 0;

				auto TargetData = new FConfig;

				auto& Array = CurrentObj->AsObject()->GetArrayField(TEXT("c"));

				TargetData->MyID = IDNumber++;
				TargetData->Version = Array[Index++]->AsObject()->GetNumberField(TEXT("v"));

				OutSheet.Add(FString::FromInt(TargetData->Version), MakeShareable<FConfig>(TargetData));
			}
			break;
		}
		case ESheetType::Sword:
		{
			uint32 IDNumber = 0;
			for (const auto& CurrentObj : ParserTarget)
			{
				uint8 Index = 0;

				auto  TargetData = new FSword;

				auto& Array = CurrentObj->AsObject()->GetArrayField(TEXT("c"));

				TargetData->MyID = IDNumber++;
				TargetData->Name = Array[Index++]->AsObject()->GetStringField(TEXT("v"));
				TargetData->Level = Array[Index++]->AsObject()->GetIntegerField(TEXT("v"));
				TargetData->Attack = Array[Index++]->AsObject()->GetNumberField(TEXT("v"));
				TargetData->Option = Array[Index++]->AsObject()->GetStringField(TEXT("v"));
				TargetData->Range = Array[Index++]->AsObject()->GetNumberField(TEXT("v"));

				OutSheet.Add(TargetData->Name, MakeShareable<FSword>(TargetData));
			}
			break;
		}
		default:
			break;
		}
	}

	//static FORCEINLINE TMap<FString, FSheetBase*> MakeSheetTable
	static FORCEINLINE TMap<FString, TSharedPtr<FSheetBase>> MakeSheetTable
	(const TArray<TSharedPtr<FJsonValue>>& ParserTarget,
		const ESheetType& PassType)
	{
		// TMap<FString, FSheetBase*> ReturnSheetData;
		TMap<FString, TSharedPtr<FSheetBase>> ReturnSheetData;
		MakeSheetByType(ReturnSheetData, PassType, ParserTarget);
		return ReturnSheetData;
	}
};




UCLASS()
class RPG_API UGlobal : public UObject
{
	GENERATED_BODY()
};
