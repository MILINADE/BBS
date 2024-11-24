// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/ItemActor.h"
#include "Inventory/ItemData.h"

// Sets default values
AItemActor::AItemActor()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	RootComponent = ItemMeshComponent;
	
}

void AItemActor::SetItemData(const FItemData& Data)
{
	ItemData = Data;

	if (ItemData.ItemMesh)
	{
		ItemMeshComponent->SetStaticMesh(ItemData.ItemMesh);
		ItemMeshComponent->SetSimulatePhysics(true);
		ItemMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		ItemMeshComponent->SetMassOverrideInKg(NAME_None, 50.0f, true);
	}
}