// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector AimingPoint, float ProjectileLaunchSpeed)
{
	FVector ProjectileLaunchVelocity = FVector(0.0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = false;
	if (!Barrel)
	{
		UE_LOG(LogTemp, Warning, TEXT("No barrel attached to %s"), *GetOwner()->GetName());
		return;
	}
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
		if (bHaveAimSolution)
		{
			//We should aim using not a velocity vector, but a unit vector, which shows direction without velocity by itself
			auto AimDirection = ProjectileLaunchVelocity.GetSafeNormal();
			MoveBarrel(&AimDirection);
		}
		//if no solution how to aim - do nothing
	}
}

void UTankAimingComponent::MoveBarrel(FVector* AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection->Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(5); //TODO remove magic number
	
	return;
}
