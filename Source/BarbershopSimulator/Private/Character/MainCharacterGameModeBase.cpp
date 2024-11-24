// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MainCharacterGameModeBase.h"
#include "Character/MainCharacter.h"
#include "Inventory/ItemActor.h"

AMainCharacterGameModeBase::AMainCharacterGameModeBase()
{
	DefaultPawnClass = AMainCharacter::StaticClass();
}

void AMainCharacterGameModeBase::BeginPlay()
{
	Super::BeginPlay();

}
