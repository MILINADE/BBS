// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/STUBaseCharacter/Component/STUCharacterMovementComponent.h"
#include "Character/STUBaseCharacter/STUBaseCharacter.h"

float USTUCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();

	const ASTUBaseCharacter* Player = Cast<ASTUBaseCharacter>(GetPawnOwner());
	return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
