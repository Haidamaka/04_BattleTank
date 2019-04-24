// Fill out your copyright notice in the Description page of Project Settings.

#include "MainTurretProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "Engine/Public/TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/Classes/GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AMainTurretProjectile::AMainTurretProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Projectile mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Projectile launch blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Projectile impact blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ImpactForce = CreateDefaultSubobject<URadialForceComponent>(FName("Impact Force"));
	ImpactForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile movement"));
	ProjectileMovement->bAutoActivate = false;
	
}

// Called when the game starts or when spawned
void AMainTurretProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AMainTurretProjectile::OnHit);
}

void AMainTurretProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ImpactForce->FireImpulse();

	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(
		this,
		ProjectileDamage,
		GetActorLocation(),
		ImpactForce->Radius,
		UDamageType::StaticClass(),
		TArray<AActor*>() //damage all actors
		);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMainTurretProjectile::DestroyProjectile, DestroyDelay);
}

void AMainTurretProjectile::DestroyProjectile()
{
	Destroy();
}


void AMainTurretProjectile::LaunchProjectile(float Speed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
}

