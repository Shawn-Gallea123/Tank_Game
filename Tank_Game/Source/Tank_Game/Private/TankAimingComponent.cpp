// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Engine.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay() {
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickfunction) {
	if ((GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds) {
		FiringStatus = EFiringStatus::Reloading;
	}
	// TODO Handle aiming and locked states
}

void UTankAimingComponent::Initialize(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation) {
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace);

	if (bHaveAimSolution) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		FVector fv = FVector(100., 0., 0.);
		MoveBarrel(AimDirection);
		//auto Name = GetOwner()->GetName();
		//auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found for %s"), Time, *Name);
	}
	else {
		//auto Time = GetWorld()->GetTimeSeconds();
		//auto Name = GetOwner()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("%f: Cannot find a solution for %s"), Time, *Name);
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection) {

	if (!ensure(Barrel && Turret)) {
		return;
	}

	// Work-out difference between current Barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);

}

void UTankAimingComponent::FireCannon() {

	if (FiringStatus != EFiringStatus::Reloading) {

		if (!ensure(Barrel)) {
			return;
		}

		if (!ensure(ProjectileBlueprint)) {
			return;
		}

		// Spawn a projectile at the firing socket location on the Barrel
		// Captured the projectile using the return value to call Launch on it
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();

	}

}