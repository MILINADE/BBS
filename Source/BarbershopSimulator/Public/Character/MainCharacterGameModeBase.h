// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainCharacterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BARBERSHOPSIMULATOR_API AMainCharacterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMainCharacterGameModeBase();

public:
	virtual void BeginPlay() override;
};
