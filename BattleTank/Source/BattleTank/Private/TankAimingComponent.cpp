// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "MainTurretProjectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::Initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector AimingPoint)
{
	FVector ProjectileLaunchVelocity = FVector(0.0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = false;
	if (!ensure(Turret && Barrel)) { return; }
	else
	{
		//getting velocity so we could find the direction to which move the barrel
		bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
		(
			this,
			ProjectileLaunchVelocity,
			StartLocation,
			AimingPoint,
			ProjectileLaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);
		auto Time = GetWorld()->GetTimeSeconds();
		if (bHaveAimSolution)
		{
			//We should aim using not a velocity vector, but a unit vector, which shows direction without velocity by itself
			auto AimDirection = ProjectileLaunchVelocity.GetSafeNormal();
			MoveBarrel(&AimDirection);
			//MoveTurret(&AimDirection);
		}
		//if no solution how to aim - do nothing
	}
}

void UTankAimingComponent::MoveBarrel(FVector* AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection->Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::MoveTurret(FVector * AimDirection)
{
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection->Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;

	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::FireMainTurret()
{
	if (!ensure(Barrel)) { return; }
	if (!ensure(ProjectileBlueprint)) { return; }
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
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile"))
				);
		Projectile->LaunchProjectile(ProjectileLaunchSpeed);
		lastMTfire = Time;
	}
}
