// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	//moving barrel at set speed based on the frame time and required elevation degree
	auto ElevationChange = FMath::Clamp<float>(RelativeSpeed, -1, +1) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawElevation = RelativeRotation.Pitch + ElevationChange;
	auto CorrectedElevation = FMath::Clamp(RawElevation, MinElevationDegree, MaxElevationDegree);

	SetRelativeRotation(FRotator(CorrectedElevation, 0, 0));
	return;
}



