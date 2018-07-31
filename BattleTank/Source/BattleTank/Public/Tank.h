// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
	float ProjectileLaunchSpeed = 100000.0; //find sensible default

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

public:	
	//Set the barrel to move while aiming
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UStaticMeshComponent* BarrelToSet);

	//Start moving barrel to aim it at set location
	void AimAt(FVector HitLocation);
	
	
	
};
