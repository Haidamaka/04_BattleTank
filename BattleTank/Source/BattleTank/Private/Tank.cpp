// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TankAimingComponent.h"
#include "MainTurretProjectile.h"
#include "TankBarrel.h"
#include "TankTrack.h"
#include "MainTurretProjectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}



// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation, ProjectileLaunchSpeed);
}

void ATank::FireMainTurret()
{
	if (!ensure(Barrel)) { return; }
	auto Time = GetWorld()->GetTimeSeconds();
	bool isReloaded = false;
	if (lastMTfire == 0)
	{
		isReloaded = true;
	}
	else
	{
		isReloaded = ((Time - lastMTfire) > ReloadTime);
	}

	if (isReloaded)
	//Spawning projectile at Projectile socket location of the Barrel
	{
		auto Projectile = GetWorld()->SpawnActor<AMainTurretProjectile>
			(
				MainTurretProjectile,
				Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile"))
				);
		Projectile->LaunchProjectile(ProjectileLaunchSpeed);
		lastMTfire = Time;
	}
}

