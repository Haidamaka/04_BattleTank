// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainTurretProjectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class BATTLETANK_API AMainTurretProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainTurretProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UProjectileMovementComponent* ProjectileMovement = nullptr;
	void LaunchProjectile(float Speed);
	
};
