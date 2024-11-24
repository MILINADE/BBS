// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/STUBaseCharacter/STUBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Actors/Basket/Basket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/STUBaseCharacter/STUBaseCharacterAnimInstance.h"
#include "Character/STUBaseCharacter/Component/STUCharacterMovementComponent.h"
#include "Character/STUBaseCharacter/Component/STUHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Controller.h"
#include "Weapon/STUBaseWeapon.h"
#include "Component/STUWeaponComponent.h"
#include "Components/CapsuleComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*if (RootComponent == nullptr)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	}*/


	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->bUsePawnControlRotation = false;
	CameraComponent->SetupAttachment(SpringArmComponent);

	ItemHolder = CreateDefaultSubobject<USceneComponent>(TEXT("ItemHolder"));
	ItemHolder->SetupAttachment(RootComponent);
	ItemHolder->SetRelativeLocation(FVector(50.0f, 0.0f, 0.0f));

	SpringArmHolder = CreateDefaultSubobject<USceneComponent>(TEXT("SpringArmHolder"));
	FName SocketName = FName("headSocket");
	//SpringArmHolder->SetupAttachment(GetMesh(), SocketName);
	SpringArmHolder->SetupAttachment(RootComponent);

	SpringArmComponent->SetupAttachment(SpringArmHolder);

	HealthComponent = CreateDefaultSubobject<USTUHealthComponent>(TEXT("HealthComponent"));

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HealthRenderComponent"));
	HealthTextComponent->SetupAttachment(RootComponent);

	WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>(TEXT("WeaponComponent"));

}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(HealthTextComponent);
	check(GetCharacterMovement());
	check(GetMesh());
	
	OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
	HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);
	LandedDelegate.AddDynamic(this, &ASTUBaseCharacter::OnGroundLanded);
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	check(WeaponComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ASTUBaseCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::LookUp);

	PlayerInputComponent->BindAction("Jump",IE_Pressed, this,  &ASTUBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Interact",IE_Pressed, this,  &ASTUBaseCharacter::InteractWithObject);
	PlayerInputComponent->BindAction("Run",IE_Pressed, this,  &ASTUBaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run",IE_Released, this,  &ASTUBaseCharacter::OnEndRunning);
	PlayerInputComponent->BindAction("Fire",IE_Pressed, WeaponComponent, &USTUWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTUWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USTUWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USTUWeaponComponent::Reload);
}

bool ASTUBaseCharacter::IsRunning() const
{
	return bWantsToRun && bIsMovingForward && !GetVelocity().IsZero();
}

float ASTUBaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero())
	{
		return 0.0f;
	}

	const auto VelosityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelosityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelosityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

float ASTUBaseCharacter::GetMovementRightDirection() const
{
	if (RightInput != 0.0f)
	{
		return RightInput;
	}
	else
	{
		return RightInput;
	}
}

void ASTUBaseCharacter::MoveForward(float Value)
{
	bIsMovingForward = Value > 0.0f;
	if (Value == 0.0f) return;
	AddMovementInput(GetActorForwardVector(), Value);
}

void ASTUBaseCharacter::MoveRight(float Value)
{
	RightInput = Value;
	if (Value == 0.0f) return;
	AddMovementInput(GetActorRightVector(), Value);
}

void ASTUBaseCharacter::OnStartRunning()
{
	bWantsToRun = true;
}

void ASTUBaseCharacter::OnEndRunning()
{
	bWantsToRun = false;
}

void ASTUBaseCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ASTUBaseCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ASTUBaseCharacter::OnDeath()
{
	UE_LOG(BaseCharacterLog, Display, TEXT("Player %s is dead!"), *GetName());
	
	PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5.0f);

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponComponent->StopFire();

	//SimulationDeath
	//GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//GetMesh()->SetSimulatePhysics(true);
}

void ASTUBaseCharacter::OnHealthChanged(float Health, float HealthDelta)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}



void ASTUBaseCharacter::InteractWithObject()
{
	FHitResult HitResult;
	FVector Start = CameraComponent->GetComponentLocation();
	FVector End = Start + (CameraComponent->GetForwardVector() * InteractDistance);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHitResult = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);

	if (bHitResult)
	{
		AActor* HitActor = HitResult.GetActor();
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.0f, 0, 1.0f);
		if (HitActor != nullptr && HitActor->IsA(ABasket::StaticClass()))
		{
			GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Black, FString::Printf(TEXT("HitResult: %s"), *HitResult.GetActor()->GetName()));
			HitActor->AttachToComponent(ItemHolder, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			//PickUpBasket(Cast<ABasket>(HitActor));
		}
		else 
		{
			GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Black, TEXT("HitActor == nullptr"));
		}
	}
}

void ASTUBaseCharacter::PickUpBasket(ABasket* HitActorBasket)
{
	HitActorBasket->AttachToComponent(ItemHolder,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void ASTUBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetVelocity().Z;
	UE_LOG(BaseCharacterLog, Display, TEXT("On landed: %f"), FallVelocityZ);

	if (FallVelocityZ < LandedDamaveVelocity.X)
	{
		return;
	}
	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamaveVelocity, LandedDamage, FallVelocityZ);
	UE_LOG(BaseCharacterLog, Display, TEXT("On landed: %f"), FinalDamage);
	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}
