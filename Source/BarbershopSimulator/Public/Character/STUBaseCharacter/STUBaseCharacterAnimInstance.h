// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "STUBaseCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BARBERSHOPSIMULATOR_API USTUBaseCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeBeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnAnimationStart();

	UFUNCTION(BlueprintCallable)
	void OnAnimationEnd();

	bool GetJumpAnimationActive() const { return bJumpAnimationActive; }
	bool GetWeaponInHands() const { return bWeaponInHands; }

private:
	bool bJumpAnimationActive;

	bool bWeaponInHands = false;
	
};
