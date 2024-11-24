// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Basket/Basket.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Actors/Basket/InventoryComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
ABasket::ABasket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));


	BasketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BasketMesh"));
	BasketMesh->SetupAttachment(RootComponent);

	BasketInventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("BasketInventory"));

	for (int32 i = 0; i < 9; i++)
	{
		FString PointName = FString::Printf(TEXT("AttachPoint_%d"), i);
		USceneComponent* AttachPoint = CreateDefaultSubobject<USceneComponent>(*PointName);
		AttachPoint->SetupAttachment(RootComponent);
		AttachPoints.Add(AttachPoint);
	}

	AttachPoints[0]->SetRelativeLocation(FVector(18.0f, 9.0f, 0.0f));
	AttachPoints[1]->SetRelativeLocation(FVector(0.0f, 9.0f, 0.0f));
	AttachPoints[2]->SetRelativeLocation(FVector(-18.0f, 9.0f, 0.0f));

	AttachPoints[3]->SetRelativeLocation(FVector(18.0f, 0.0f, 0.0f));
	AttachPoints[4]->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	AttachPoints[5]->SetRelativeLocation(FVector(-18.0f, 0.0f, 0.0f));

	AttachPoints[6]->SetRelativeLocation(FVector(18.0f, -9.0f, 0.0f));
	AttachPoints[7]->SetRelativeLocation(FVector(0.0f, -9.0f, 0.0f));
	AttachPoints[8]->SetRelativeLocation(FVector(-18.0f, -9.0f, 0.0f));


}

void ABasket::AddItemToBasket(AItemActor* Item)
{
	if (!Item || AttachPoints.Num() == 0)
	{
		return;
	}

	for (USceneComponent* AttachPoint : AttachPoints)
	{
		if (AttachPoint) //&& !Item->IsAttachedTo(Cast<AActor>(AttachPoint))
		{
			UStaticMeshComponent* ItemMesh = Item->FindComponentByClass<UStaticMeshComponent>();
			if (ItemMesh)
			{
				FVector MeshSize = ItemMesh->Bounds.BoxExtent;
				FVector BasketSpaceSize(FVector(9.0f, 9.0f, 9.0f));

				USceneComponent* ItemRootComponent = Item->GetRootComponent();

				if (MeshSize.X > BasketSpaceSize.X || MeshSize.Y > BasketSpaceSize.Y || MeshSize.Z > BasketSpaceSize.Z)
				{
					FVector NewWorldScale = BasketSpaceSize / MeshSize;
					ItemMesh->SetWorldScale3D(NewWorldScale);
				}
				//Item->AttachToComponent(AttachPoint, FAttachmentTransformRules::KeepWorldTransform);
				//ItemMesh->AttachToComponent(AttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
				//ItemRootComponent->AttachToComponent(AttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);

				if (AttachPoint)
				{
					ItemMesh->AttachToComponent(AttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
					GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Red, TEXT("ItemMesh"));
				}
				else
				{
					GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Red, TEXT("ItemMesh nullptr"));
				}
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Red, TEXT("ItemMesh nullptr"));
			}
		}
	}

	/*if (BasketInventory && Item)
	{
		BasketInventory->AddItem(Item);
		UStaticMeshComponent* ItemMeshComponent = Cast<UStaticMeshComponent>(Item->GetItemMeshComponent());

		ItemMeshComponent->SetSimulatePhysics(false);
		ItemMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ItemMeshComponent->SetRelativeRotation(BasketMesh->GetRelativeRotation());

		ItemMeshComponent->AttachToComponent(BasketMesh, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}*/
}
