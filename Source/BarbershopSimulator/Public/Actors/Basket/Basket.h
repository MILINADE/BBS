// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Inventory/ItemActor.h"
#include "Basket.generated.h"

class UStaticMeshComponent;
class UInventoryComponent;

UCLASS()
class BARBERSHOPSIMULATOR_API ABasket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasket();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Basket|Mesh")
	UStaticMeshComponent* BasketMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basket|Inventory")
	UInventoryComponent* BasketInventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basket|AttachPoints")
	TArray<USceneComponent*> AttachPoints;

public:	

	void AddItemToBasket(class AItemActor* Item);

};
