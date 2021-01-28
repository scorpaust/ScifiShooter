// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScifiShooterGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SCIFISHOOTER_API AKillEmAllGameMode : public AScifiShooterGameModeBase
{
	GENERATED_BODY()
	
public:

	virtual void PawnKilled(APawn* PawnKilled) override;

	void EndGame(bool bIsPlayerWinner);
};
