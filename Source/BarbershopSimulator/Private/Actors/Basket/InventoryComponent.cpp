// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Basket/InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UInventoryComponent::AddItem(AItemActor* Item)
{
	if (Item)
	{
		Items.Add(Item);
		return true;
	}
	return false;
}

bool UInventoryComponent::RemoveItem(AItemActor* Item)
{
	return Items.Remove(Item) > 0;
}

