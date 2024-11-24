// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AD_HUD.h"
#include "GameFramework/HUD.h"
#include "Engine\Canvas.h"

void AAD_HUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrosshair();
}

void AAD_HUD::DrawCrosshair()
{
    FLinearColor RectColor = FLinearColor::Black;

    FVector2D ScreenDimensions(Canvas->SizeX, Canvas->SizeY);

    FVector2D CrosshairPosition(ScreenDimensions.X / 2.0f, ScreenDimensions.Y / 2.0f);

    float CrosshairSize = 5.0f;

    DrawRect(RectColor, CrosshairPosition.X - (CrosshairSize / 2.0f), CrosshairPosition.Y - (CrosshairSize / 2.0f), CrosshairSize, CrosshairSize);
}
