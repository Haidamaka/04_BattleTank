// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	//UE_LOG(LogTemp, Warning, TEXT("wroooom"))
	Throttle = FMath::Clamp<float>(Throttle, -1, +1);
	auto ForceApplied = GetForwardVector()*Throttle*TrackMaxDrivingForce;
	auto ForceLoaction = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLoaction);
}



