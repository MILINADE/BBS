// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/STUBaseCharacter/STUBaseCharacter.h"
#include "Component/STUAIWeaponComponent.h"
#include "STUAICharacter.generated.h"

/**
 * 
 */
class UBehaviorTree;

UCLASS()
class BARBERSHOPSIMULATOR_API ASTUAICharacter : public ASTUBaseCharacter
{
	GENERATED_BODY()

public:
	ASTUAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

protected:
	virtual void OnDeath() override;

};
