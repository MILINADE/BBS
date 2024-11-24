// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemData.h"
#include "ItemActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class BARBERSHOPSIMULATOR_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemActor();

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ItemMeshComponent;

	FItemData ItemData;

public:

	void SetItemData(const FItemData& ItemData);

	UStaticMeshComponent* GetItemMeshComponent() const { return ItemMeshComponent; }
};