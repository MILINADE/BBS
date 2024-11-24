// Fill out your copyright notice in the Description page of Project Settings.


#include "AIItem/AIItem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AAIItem::AAIItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(RootComponent);

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	Collision->SetupAttachment(ItemMesh);

	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void AAIItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAIItem::PickUp()
{
	ItemMesh->SetSimulatePhysics(false);
	//TODO
}

void AAIItem::Drop()
{
	ItemMesh->SetSimulatePhysics(true);
}

