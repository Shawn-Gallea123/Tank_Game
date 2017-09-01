// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class TANK_GAME_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	void LaunchProjectile(float Speed);

private:
	UProjectileMovementComponent *ProjectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent *LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent *ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent *ExplosionForce = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float DestroyDelay = 5.0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ProjectileDamage = 20.0;

	void OnTimerExpire();

	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult &Hit);
	
	
};
