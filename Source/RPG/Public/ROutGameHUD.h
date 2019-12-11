// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RHUDBase.h"
#include "ROutGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API AROutGameHUD : public ARHUDBase {
	GENERATED_BODY()

public:
	AROutGameHUD();

protected:
	virtual void BeginPlay() override;
};
