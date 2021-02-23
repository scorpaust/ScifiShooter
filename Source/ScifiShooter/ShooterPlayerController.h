// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterCharacter.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SCIFISHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AShooterPlayerController();

	virtual void GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) override;

	UFUNCTION()
	void ShowHud();

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	float RestartDelay;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HudClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LoseScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WinScreenClass;

	UPROPERTY()
	UUserWidget* Hud;

	FTimerHandle RestartTimer;

	FTimerHandle ShowHudTimer;

};
