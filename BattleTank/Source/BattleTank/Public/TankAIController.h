// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetPawn(APawn *InPawn) override;

	UFUNCTION()
	void OnTankDeath();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float AcceptableDistance = 8000; // check measurement unit


public:

};
