// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(RPG, Log, All);

/* Default information */
#define RLOG_INFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

/* Log default information */
#define RLOG_D(Verbosity) UE_LOG(RPG, Verbosity, TEXT("%s"), *RLOG_INFO)

/* Log customized text */
#define RLOG(Verbosity, Format, ...) UE_LOG(RPG, Verbosity, TEXT("%s%s"), *RLOG_INFO, *FString::Printf(Format, ##__VA_ARGS__))

/* Check for error, but not stop */
#define RLOGCHECK(Expr, ...) { if(!(Expr)) { RLOG(Error, TEXT("FATAL ERROR : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__; }} 

