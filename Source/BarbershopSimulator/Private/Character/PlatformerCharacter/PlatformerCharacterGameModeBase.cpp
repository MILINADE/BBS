// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlatformerCharacter/PlatformerCharacterGameModeBase.h"
#include "Character/PlatformerCharacter/PlatformerCharacter.h"
#include "Character/PlatformerCharacter/PlatformerCharacterController.h"

APlatformerCharacterGameModeBase::APlatformerCharacterGameModeBase()
{
	DefaultPawnClass = APlatformerCharacter::StaticClass();
	PlayerControllerClass = APlatformerCharacterController::StaticClass();
}
