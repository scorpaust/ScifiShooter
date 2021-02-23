// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "ScifiShooterGameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RotationRate = 10.f;

	MaxHealth = 100.f;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));

	Gun->SetOwner(this);

}

bool AShooterCharacter::IsDead() const {

	return Health <= 0.f;

}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	DamageToApply = FMath::Min(Health, DamageToApply);

	Health -= DamageToApply;

	UE_LOG(LogTemp, Warning, TEXT("Health left: %f"), Health);

	if (IsDead()) {

		AScifiShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AScifiShooterGameModeBase>();

		if (GameMode != nullptr) {

			GameMode->PawnKilled(this);

		}

		DetachFromControllerPendingDestroy();

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterCharacter::MoveForward);

	PlayerInputComponent->BindAxis("LookUp", this, &AShooterCharacter::LookUp);

	PlayerInputComponent->BindAxis("LookUpRate", this, &AShooterCharacter::LookUpRate);

	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookRight", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAxis("LookRightRate", this, &AShooterCharacter::LookRightRate);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);

}

void AShooterCharacter::MoveForward(float AxisValue) {

		if (AxisValue != 0.f) {

			AddMovementInput(GetActorForwardVector() * AxisValue);

		}
}

void AShooterCharacter::LookUp(float AxisValue) {

	AddControllerPitchInput(AxisValue);

}

void AShooterCharacter::LookUpRate(float AxisValue) {

	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());

}

void AShooterCharacter::LookRightRate(float AxisValue) {

	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());

}

void AShooterCharacter::MoveRight(float AxisValue) {

	if (AxisValue != 0.f) {

		AddMovementInput(GetActorRightVector() * AxisValue);

	}
} 

void AShooterCharacter::Shoot() {

	Gun->PullTrigger();

}

float AShooterCharacter::GetHealthPercent() const {

	return Health / MaxHealth;

}
