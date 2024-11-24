// Fill out your copyright notice in the Description page of Project Settings.


#include "AIItem/ItemSpawner.h"
#include "Inventory/ItemData.h"
#include "Inventory/ItemActor.h"

// Sets default values
AItemSpawner::AItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnItem();
}

void AItemSpawner::SpawnItem()
{
	if (!ItemDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemDataTable is not set!"));
		return;
	}

	static const FString ContextString(TEXT("Row Name"));

	TArray<FItemData*> AllItems;
	ItemDataTable->GetAllRows<FItemData>(ContextString, AllItems);

	if (AllItems.Num() > 0)
	{
		FItemData* ItemToSpawn = AllItems[0];

		if (ItemToSpawn)
		{
			FVector SpawnLocation = GetActorLocation();
			FRotator SpawnRotation = GetActorRotation();

			AItemActor* SpawnedActor = GetWorld()->SpawnActor<AItemActor>(AItemActor::StaticClass(), SpawnLocation, SpawnRotation);

			if (SpawnedActor)
			{
				SpawnedActor->SetItemData(*ItemToSpawn);
			}
		}
	}
}
