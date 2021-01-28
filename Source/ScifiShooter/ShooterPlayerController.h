// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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

private:

	UPROPERTY(EditAnywhere)
	float RestartDelay;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LoseScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WinScreenClass;

	FTimerHandle RestartTimer;

};