// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine.h"

void UTankTurret::Rotate(float RotationSpeed) {
	RotationSpeed = FMath::Clamp<float>(RotationSpeed, -1., 1.);

	auto RotationChange = RotationSpeed * MaxRotationSpeed * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;

	UE_LOG(LogTemp, Warning, TEXT("Rotate called"));

	SetRelativeRotation(FRotator(0, RawNewRotation, 0));

}

