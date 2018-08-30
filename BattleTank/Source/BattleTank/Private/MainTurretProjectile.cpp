// Fill out your copyright notice in the Description page of Project Settings.

#include "MainTurretProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMainTurretProjectile::AMainTurretProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile movement"));
	ProjectileMovement->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AMainTurretProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainTurretProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainTurretProjectile::LaunchProjectile(float Speed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
}
