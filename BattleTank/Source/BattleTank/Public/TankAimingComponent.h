// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UStaticMeshComponent* Barrel = nullptr;
	void MoveBarrel(FVector* AimDirection);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Set the barrel to move while aiming
	void SetBarrelReference(UStaticMeshComponent* BarrelToSet);
	//Move the barrel to aim at some location
	virtual void AimAt(FVector AimingPoint, float ProjectileLaunchSpeed);
	
};
