// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ABasket;
class USTUBaseCharacterAnimInstance;
class USTUHealthComponent;
class UTextRenderComponent;
class UAnimMontage;
class USTUWeaponComponent;

UCLASS()
class BARBERSHOPSIMULATOR_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTUBaseCharacter(const FObjectInitializer& ObjInit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* ItemHolder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* SpringArmHolder;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USTUBaseCharacterAnimInstance* AnimInstance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	float InteractDistance = 300.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USTUHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UTextRenderComponent* HealthTextComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USTUWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	FVector2D LandedDamaveVelocity = FVector2D(900.0f, 1200.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

	virtual void OnDeath();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsRunning() const;	

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool WeaponInHands() const { return bWeaponInHands; }

	void SetWeaponInHands(bool Value) { bWeaponInHands = Value; }

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementRightDirection() const;

private:

	bool bWantsToRun = false;
	bool bIsMovingForward = false;
	bool bWeaponInHands = false;

	float RightInput = 0.0f;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void OnStartRunning();
	void OnEndRunning();

	void LookUp(float Value);
	void Turn(float Value);

	void OnHealthChanged(float Health, float HealthDelta);
	
	void InteractWithObject();
	void PickUpBasket(ABasket* HitActorBasket);

	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);
};
