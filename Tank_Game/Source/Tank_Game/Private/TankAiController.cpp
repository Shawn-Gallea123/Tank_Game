// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "Engine.h"

void ATankAiController::BeginPlay() {
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();

	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Tank found player: %s"), *PlayerTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("AI Tank did not find player"));
	}

}

ATank * ATankAiController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAiController::GetPlayerTank() const {
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerTank) {
		return Cast<ATank>(PlayerTank);
	}
	else {
		return nullptr;
	}
}