// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MainCharacter.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Actors/Basket/Basket.h"
#include "Inventory/ItemActor.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 0.0f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArm);
	CameraComponent->bUsePawnControlRotation = false;

	GetCharacterMovement()->MaxWalkSpeed = 600.0f;

	ItemHolder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemHolder"));
	ItemHolder->SetupAttachment(RootComponent);
	ItemHolder->SetRelativeLocation(FVector(10.0f, 0.0f, 0.0f), false);
	ItemHolder->SetRelativeRotation(FRotator(0.0f,90.0f,0.0f), false);
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	/*if (CrosshairWidgetClass)
	{
		CrosshairWidget = CreateWidget<UUserWidget>(GetWorld(), CrosshairWidgetClass);
	}*/
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//CheckObjectInView();

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMainCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Pickup", IE_Pressed, this, &AMainCharacter::PickUpCheck);
}

/*void AMainCharacter::CheckObjectInView()
{
	FHitResult HitResult;
	FVector Start = CameraComponent->GetComponentLocation();
	FVector End = Start + (CameraComponent->GetForwardVector() * PickUpDistance);
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);


	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, CollisionParams);
	if (bHit && HitResult.GetActor() && HitResult.GetActor()->IsA(ABasket::StaticClass()) || HitResult.GetActor()->IsA(AItemActor::StaticClass()))
	{
		if (CrosshairWidget && !CrosshairWidget->IsInViewport())
		{
			CrosshairWidget->AddToViewport();
		}
	}
	else
	{
		if (CrosshairWidget && CrosshairWidget->IsInViewport())
		{
			CrosshairWidget->RemoveFromParent();
		}
	}
}*/

void AMainCharacter::PickUpCheck()
{
	if (GetPlayerHandsFreeState())
	{
		PickUpBasket();
	}
	else
	{
		DropOrAddToBasket();
	}
}

void AMainCharacter::PickUpBasket()
{
	FHitResult HitResult;
	FVector Start = CameraComponent->GetComponentLocation();
	FVector End = Start + (CameraComponent->GetForwardVector() * PickUpDistance);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, CollisionParams);

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();

		if (HitActor != nullptr && HitActor->IsA(ABasket::StaticClass()))
		{
			CurrentBasket = Cast<ABasket>(HitActor);

			SetPlayerHandsFreeState(false);
			GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Black, FString::Printf(TEXT("HitResult: %s"), *HitResult.GetActor()->GetName()));

			UStaticMeshComponent* HitComponent = Cast<UStaticMeshComponent>(HitResult.Component);
			if (HitComponent)
			{
				HitComponent->SetSimulatePhysics(false);
				HitComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				HitComponent->SetRelativeRotation(ItemHolder->GetRelativeRotation());

				HitComponent->AttachToComponent(ItemHolder, FAttachmentTransformRules::SnapToTargetIncludingScale);
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Black, FString::Printf(TEXT("HitResult: Not ABasket")));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Black, FString::Printf(TEXT("HitResult: nillptr")));
	}
}

void AMainCharacter::DropOrAddToBasket()
{
	FHitResult HitResult;
	FVector Start = CameraComponent->GetComponentLocation();
	FVector End = Start + (CameraComponent->GetForwardVector() * PickUpDistance);
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, CollisionParams);

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 5, 0, 5);
		if (HitActor != nullptr && HitActor->IsA(AItemActor::StaticClass()))
		{
			CurrentBasket->AddItemToBasket(Cast<AItemActor>(HitActor));
			
			//GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Black, FString::Printf(TEXT("AddToBasket")));
		}
		else
		{
			DropBasket();
		}

	}
	else
	{
		DropBasket();
	}
}

void AMainCharacter::DropBasket()
{
	TArray<USceneComponent*> AttachedComponents = ItemHolder->GetAttachChildren();

	for (USceneComponent* Component : AttachedComponents)
	{
		if (Component)
		{
			UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(Component);
			if (MeshComponent)
			{
				SetPlayerHandsFreeState(true);

				MeshComponent->SetSimulatePhysics(true);
				MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

				MeshComponent->SetWorldLocation(RootComponent->GetComponentLocation() + RootComponent->GetForwardVector() * 100.f);
				MeshComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
				GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Black, FString::Printf(TEXT("Detach")));

			}
		}
	}
}

void AMainCharacter::MoveForward(float Value)
{
	if (Value != 0.0f) 
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMainCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

/*void AMainCharacter::ClampPitch(float Value)
{
	FRotator NewRotation = Controller->GetControlRotation();
	NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + Value, MinPitch, MaxPitch);
	Controller->SetControlRotation(NewRotation);
}*/
