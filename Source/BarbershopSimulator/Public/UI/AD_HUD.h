// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AD_HUD.generated.h"

/**
 * 
 */
UCLASS()
class BARBERSHOPSIMULATOR_API AAD_HUD : public AHUD
{
	GENERATED_BODY()
	
	virtual void DrawHUD() override;
	
	void DrawCrosshair();
};
