// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AMainTurretProjectile;
class UTankMovementComponent;

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

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ProjectileLaunchSpeed = 4000.0;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 3.0;

	UPROPERTY(EditAnywhere, Category = Firing)
	TSubclassOf<AMainTurretProjectile> MainTurretProjectile;

	//Local barrel ref to spawn projectile
	UTankBarrel* Barrel = nullptr;

	//world time when main turret fired previously to calculate reload
	float lastMTfire = 0;
protected:
	UTankAimingComponent* TankAimingComponent = nullptr;
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

public:	
	//Set the barrel to move while aiming
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	//Set turret ref to move while aiming
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	//Start moving barrel to aim it at set location
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Controlls)
	void FireMainTurret();

};
