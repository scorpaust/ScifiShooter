// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"


AShooterPlayerController::AShooterPlayerController() {

	RestartDelay = 5.f;

}

void AShooterPlayerController::BeginPlay() {

	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(ShowHudTimer, this, &AShooterPlayerController::ShowHud, 7.0f, false);

}


void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) {

	Super::GameHasEnded(EndGameFocus, bIsWinner);

	Hud->RemoveFromViewport();

	if (bIsWinner) {

		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);

		if (WinScreen != nullptr) {

			WinScreen->AddToViewport();

		}

	}
	else {

		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);

		if (LoseScreen != nullptr) {

			LoseScreen->AddToViewport();

		}

	}
	
	GetWorldTimerManager().SetTimer(RestartTimer, this, &AShooterPlayerController::RestartLevel, RestartDelay);

}

void AShooterPlayerController::ShowHud() {

	Hud = CreateWidget(this, HudClass);

	if (Hud != nullptr) {

		Hud->AddToViewport();

	}
	
	GetWorld()->GetTimerManager().ClearTimer(ShowHudTimer);

}