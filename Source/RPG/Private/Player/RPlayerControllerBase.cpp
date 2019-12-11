// Fill out your copyright notice in the Description page of Project Settings.


#include "RPlayerControllerBase.h"

ARPlayerControllerBase::ARPlayerControllerBase() {
	bShowMouseCursor = true;
	bEnableMouseOverEvents = bEnableTouchOverEvents = true;
	bEnableClickEvents = bEnableTouchEvents = true;
}