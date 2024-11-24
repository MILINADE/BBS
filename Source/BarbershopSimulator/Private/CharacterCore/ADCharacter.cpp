// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCore/ADCharacter.h"

// Sets default values
AADCharacter::AADCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AADCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AADCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AADCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

