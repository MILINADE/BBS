// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "MainCharacter.generated.h"

UCLASS()
class BARBERSHOPSIMULATOR_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|PickUp")
	class UStaticMeshComponent* HeldItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|PickUp")
	class USceneComponent* ItemHolder;

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|UI")
	TSubclassOf<UUserWidget> CrosshairWidgetClass;

	UUserWidget* CrosshairWidget;*/

	//void CheckObjectInView();

	void PickUpCheck();
	void PickUpBasket();
	void DropOrAddToBasket();
	void DropBasket();

	bool GetPlayerHandsFreeState() const { return bPlayerHandFree; }
	void SetPlayerHandsFreeState(bool bHandState) { bPlayerHandFree = bHandState; }

	float PickUpDistance = 300.0f;
private:

	void MoveForward(float Value);
	void MoveRight(float Value);

	//void ClampPitch(float Value);

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY()
	class ABasket* CurrentBasket;


	UPROPERTY(EditDefaultsOnly, Category = "Character|CameraSettings")
	float MinPitch = -80.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Character|CameraSettings")
	float MaxPitch = 80.0f;

	bool bPlayerHandFree = true;
};
