// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("%s is throttling at speed %f"), *GetName(), Throttle)

		//TODO clamp actual throttle value
}


