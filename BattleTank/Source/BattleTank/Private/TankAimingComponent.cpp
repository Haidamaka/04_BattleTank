// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "MainTurretProjectile.h"
#include "ConstructorHelpers.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<AMainTurretProjectile> Proj(TEXT("/Game/Projectile/MyMainTurretProjectile_BP"));
	if (Proj.Class)
	{
		ProjectileBlueprint = Proj.Class;
	}
	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	lastMTfire = GetWorld()->GetTimeSeconds();
	CurrentAmmo = MaxAmmo;
}

void UTankAimingComponent::Initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	bool isReloaded = ((GetWorld()->GetTimeSeconds() - lastMTfire) > ReloadTime);
	if (CurrentAmmo <= 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if (!isReloaded)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	return !(Barrel->GetForwardVector().Equals(AimDirection, 0.01));
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
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
			AimDirection = ProjectileLaunchVelocity.GetSafeNormal();
			MoveBarrel(&AimDirection);
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
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
}

void UTankAimingComponent::FireMainTurret()
{
	if (!ensure(Barrel)) { return; }
	if (!ensure(ProjectileBlueprint)) { return; }

	if ((FiringState==EFiringState::Locked) || (FiringState == EFiringState::Aiming))
		//Spawning projectile at Projectile socket location of the Barrel
	{
		auto Projectile = GetWorld()->SpawnActor<AMainTurretProjectile>
			(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile"))
				);
		Projectile->LaunchProjectile(ProjectileLaunchSpeed);
		lastMTfire = GetWorld()->GetTimeSeconds();
		CurrentAmmo--;
	}
}
