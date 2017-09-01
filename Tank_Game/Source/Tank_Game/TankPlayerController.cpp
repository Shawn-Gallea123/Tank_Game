// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("Player Tick"));
	 AimTowardsCrosshair();

}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) {
		FoundAimingComponent(AimingComponent);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Player controller can't find aiming component at BeginPlay"));
	}
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetPawn()) { return; }

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	FVector HitLocation; // OUT

	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);

	if (bGotHitLocation) {
		 AimingComponent->AimAt(HitLocation);
	}
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	
	// calculates location of the crosshair
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// "De-project" the screen position of the crosshair to a world direction

	
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// Line-trace along that direction, to see what we hit up to a max range
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const {
	FVector WorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X,
		ScreenLocation.Y,
		WorldLocation,
		LookDirection);

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility)) {
		HitLocation = HitResult.Location;
		return true;
	}

	HitLocation = FVector(0);
	return false;

}

void ATankPlayerController::OnTankDeath() {
	UE_LOG(LogTemp, Warning, TEXT("PLAYER TANK DIED"));
	StartSpectatingOnly();
}

void ATankPlayerController::SetPawn(APawn *Pawn) {
	Super::SetPawn(Pawn);
	if (Pawn) {
		auto PossessedTank = Cast<ATank>(Pawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
	}

}