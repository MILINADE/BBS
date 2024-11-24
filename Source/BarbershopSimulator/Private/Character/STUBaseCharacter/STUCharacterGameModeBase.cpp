// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/STUBaseCharacter/STUCharacterGameModeBase.h"
#include "Character/STUBaseCharacter/STUBaseCharacter.h"
#include "Character/STUBaseCharacter/STUBaseCharacterController.h"
#include "UI/STUGameHUD.h"

ASTUCharacterGameModeBase::ASTUCharacterGameModeBase()
{
	DefaultPawnClass = ASTUBaseCharacter::StaticClass();
	PlayerControllerClass = ASTUBaseCharacterController::StaticClass();
	HUDClass = ASTUGameHUD::StaticClass();
}
