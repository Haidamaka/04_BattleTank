// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

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


public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	//Set the barrel to move while aiming
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	//Set the turret to move while aiming
	void SetTurretReference(UTankTurret* TurretToSet);

	//Move turret and barrel to aim at some location
	virtual void AimAt(FVector AimingPoint, float ProjectileLaunchSpeed);
	
};
