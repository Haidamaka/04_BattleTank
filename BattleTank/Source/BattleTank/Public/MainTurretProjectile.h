// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainTurretProjectile.generated.h"


class UProjectileMovementComponent;
class UParticleSystemComponent;
class UStaticMeshComponent;
class URadialForceComponent;


UCLASS()
class BATTLETANK_API AMainTurretProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainTurretProjectile();

	void LaunchProjectile(float Speed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	URadialForceComponent* ImpactForce = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DestroyDelay = 10.0f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void DestroyProjectile();
};
