// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/STUWeaponComponent.h"
#include "STUAIWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class BARBERSHOPSIMULATOR_API USTUAIWeaponComponent : public USTUWeaponComponent
{
	GENERATED_BODY()

public:
	virtual	void StartFire() override;
	virtual void NextWeapon() override;
	
};
