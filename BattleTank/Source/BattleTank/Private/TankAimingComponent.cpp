// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector AimingPoint, float ProjectileLaunchSpeed)
{
	FVector ProjectileLaunchVelocity = FVector(0.0);
	if (!Barrel)
	{
		UE_LOG(LogTemp, Warning, TEXT("No barrel attached to %s"), *GetOwner()->GetName());
		return;
	}
	else
	{
		//getting velocity so we could find the direction to which move the barrel
		if (UGameplayStatics::SuggestProjectileVelocity
				(
					this,
					ProjectileLaunchVelocity,
					Barrel->GetSocketLocation(FName("Projectile")),
					AimingPoint,
					ProjectileLaunchSpeed,
					false,
					0,
					0,
					ESuggestProjVelocityTraceOption::DoNotTrace
				)
			)
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
	UE_LOG(LogTemp, Warning, TEXT("Gotta move barrel of %s to %s"), *GetOwner()->GetName(), *AimDirection->ToString())
	return;
}
