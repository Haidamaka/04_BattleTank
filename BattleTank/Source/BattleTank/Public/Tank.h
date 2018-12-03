// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class AMainTurretProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//TODO remove once firing is moved to AimingComponent
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ProjectileLaunchSpeed = 4000.0;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTime = 3.0;

	UPROPERTY(EditAnywhere, Category = "Firing")
	TSubclassOf<AMainTurretProjectile> MainTurretProjectile;

	//Local barrel ref to spawn projectile
	UTankBarrel* Barrel = nullptr;//TODO Remove

	//world time when main turret fired previously to calculate reload
	float lastMTfire = 0;

protected:

public:	
	UFUNCTION(BlueprintCallable, Category = "Controlls")
	void FireMainTurret();

};
