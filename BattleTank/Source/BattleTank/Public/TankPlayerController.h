// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TankPlayerController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	ATank * GetControlledTank() const;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
		float CrossHairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly)
		float CrossHairYLocation = 0.33333;
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000.0;

	//start turning barrel towards the crosshair
	virtual void AimTowardsCrosshair(); 
	//Return an OUT parameter, true if hit landscape
	bool GetSightHitLocation(FVector& OutHitLocation) const;
	//Find if we are aiming at something
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

public:

	
};
