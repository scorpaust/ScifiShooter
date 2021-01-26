// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RotationRate = 10.f;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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