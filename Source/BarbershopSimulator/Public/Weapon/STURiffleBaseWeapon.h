// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURiffleBaseWeapon.generated.h"

/**
 * 
 */

 class USTUWeaponFXComponent;
 class UNiagaraComponent;

UCLASS()
class BARBERSHOPSIMULATOR_API ASTURiffleBaseWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

public:
	ASTURiffleBaseWeapon();
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	virtual void BeginPlay() override;
	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float TimeBetWeenShots = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float BulletSpret = 1.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float DamageAmount = 10.0f;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	USTUWeaponFXComponent* WeaponFXComponent;


private:
	FTimerHandle ShotTimerHandle;

	UPROPERTY()
	UNiagaraComponent* MuzzleFXComponent;
	
	void MakeDamage(const FHitResult& HitResult);

	void InitMuzzleFX();
	void SetMuzzleFXVisibility(bool Visible);
};
