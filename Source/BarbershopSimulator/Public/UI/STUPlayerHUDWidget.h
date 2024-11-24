// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STUPlayerHUDWidget.generated.h"

class USTUWeaponComponent;
class USTUHealthComponent;

/**
 * 
 */
UCLASS()
class BARBERSHOPSIMULATOR_API USTUPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetCurrentAmmoData(FAmmoData& AmmoData, FString& AmmoDataString) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerSpectating() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnTakeDamage();

	virtual bool Initialize() override;
private:
	USTUWeaponComponent* GetWeaponComponent() const;
	USTUHealthComponent* GetHealthComponent() const;

	virtual void OnHealthChanged(float Health, float HealthDelta);
};
