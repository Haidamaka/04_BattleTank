// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */

class ASprungWheel;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
	//virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	TArray<ASprungWheel*> GetWheels() const;

public:
	UTankTrack();
	//Set Throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Controll")
	void SetThrottle(float Throttle);

	void DriveTrack(float CurrentThrottle);

	//This is max force per track in newtons
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float TrackMaxDrivingForce = 400000; //40t tank for 1G acceleration
};
