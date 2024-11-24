// Copyright Epic Games, Inc. All Rights Reserved.

#include "BarbershopSimulatorGameMode.h"
#include "BarbershopSimulatorCharacter.h"
#include "UObject/ConstructorHelpers.h"


ABarbershopSimulatorGameMode::ABarbershopSimulatorGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
