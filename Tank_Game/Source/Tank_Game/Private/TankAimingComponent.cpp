// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Engine.h"
#include "TankBarrel.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; // TODO should this tick?

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel *BarrelToSet) {
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret *TurretToSet) {
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	if (!Barrel) { return; }

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
		auto Name = GetOwner()->GetName();
		MoveBarrel(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found for %s"), Time, *Name);
	}
	else {
		auto Time = GetWorld()->GetTimeSeconds();
		auto Name = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%f: Cannot find a solution for %s"), Time, *Name);
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection) {
	// Work-out difference between current Barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AAsRotator = AimDirection.Rotation();
	auto DeltaRotator2 = AAsRotator - TurretRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator2.Yaw);

}
