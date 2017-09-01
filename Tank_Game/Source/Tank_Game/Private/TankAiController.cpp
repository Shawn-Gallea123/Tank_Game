// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "Engine.h"
#include "TankAimingComponent.h"

void ATankAiController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { 
		return;
	}

		MoveToActor(PlayerTank, AcceptanceRadius);

		// Aim towards the player
		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		EFiringStatus FiringStatus = AimingComponent->GetFiringStatus();

		if (FiringStatus == EFiringStatus::Locked || FiringStatus == EFiringStatus::Aiming) {
			AimingComponent->FireCannon();
		}
}
