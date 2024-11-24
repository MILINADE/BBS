// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/STUBaseCharacter/STUBaseCharacterAnimInstance.h"


void USTUBaseCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	bJumpAnimationActive = false;
}

void USTUBaseCharacterAnimInstance::OnAnimationStart()
{
	bJumpAnimationActive = true;
}

void USTUBaseCharacterAnimInstance::OnAnimationEnd()
{
	bJumpAnimationActive = false;
}
