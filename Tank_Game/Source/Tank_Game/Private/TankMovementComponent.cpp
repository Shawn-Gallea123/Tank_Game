// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet) {
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForeward(float Throw) {
	// UE_LOG(LogTemp, Warning, TEXT("Intend move foreward Throw: %f"), Throw);

	if (!LeftTrack || !RightTrack) {
		return;
	}

	// TODO Prevent double speed from stick + shoulders
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {

	if (!LeftTrack || !RightTrack) {
		return;
	}

	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed) {
	// Don't want to call Super, are overriding
	UE_LOG(LogTemp, Warning, TEXT("%s RequestDirectMove, MoveVelocity: %s"), *GetOwner()->GetName(), *MoveVelocity.ToString());
}



