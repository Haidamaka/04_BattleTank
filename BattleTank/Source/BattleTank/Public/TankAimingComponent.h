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

//Holds 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrel(FVector* AimDirection);
	void MoveTurret(FVector* AimDirection);
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Locked;

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	//Set the barrel to move while aiming
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);

	//Move turret and barrel to aim at some location
	virtual void AimAt(FVector AimingPoint, float ProjectileLaunchSpeed);
	
};
