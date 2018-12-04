// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//ENum for aiming status
UENUM()
enum class EFiringState : uint8 
{
	Reloading,
	Aiming,
	Locked	
};

// Forward Declaration
class UTankBarrel;
class UTankTurret;
class AMainTurretProjectile;

//Holds 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	FVector AimDirection = FVector(0);
	//world time when main turret fired previously to calculate reload
	float lastMTfire = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ProjectileLaunchSpeed = 4000.0;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTime = 3.0;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	TSubclassOf<AMainTurretProjectile> ProjectileBlueprint;

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void MoveBarrel(FVector* AimDirection);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	//Set the barrel to move while aiming
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);

	//Move turret and barrel to aim at some location
	virtual void AimAt(FVector AimingPoint);

	UFUNCTION(BlueprintCallable, Category = "Controlls")
	virtual void FireMainTurret();

	bool IsBarrelMoving();
};
