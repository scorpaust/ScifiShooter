// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SCIFISHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	AShooterAIController();

	virtual void Tick(float DeltaSeconds) override;

	bool IsDead() const;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Behaviors")
	class UBehaviorTree* AIBehavior;

};
