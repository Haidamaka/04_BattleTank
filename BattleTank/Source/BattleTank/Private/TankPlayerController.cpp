// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not posessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController posessing: %s"), *ControlledTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{

	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (GetControlledTank() == nullptr) { return; }
	
	FVector HitLocation; //out parameter
	if (GetSightHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Location: %s"), *HitLocation.ToString());


		//TODO tell controlled tank to aim at this point
	}
	return;
}

//get world location if line trace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightHitLocation(FVector& OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	FVector CameraWorldLocation;
	FVector LookDirection;

	//find the crosshair position
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D((ViewportSizeX*CrossHairXLocation), (ViewportSizeY*CrossHairYLocation));

	//De-project the screen position of the crosshair to a world direction
	//line-trace along that direction and see what we hit

	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection))
	{
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
		return true;
	}
	else
	{
		return false;
	}

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0.0);
	return false;
}

