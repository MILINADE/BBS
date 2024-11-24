// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup/STUHealthPickup.h"
#include "STUUtils.h"
#include "Character/STUBaseCharacter/Component/STUHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool ASTUHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	return HealthComponent->TryToAddHealth(HealthAmount);
}
