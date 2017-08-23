// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet) {
	if (!LeftTrackToSet || !RightTrackToSet) {
		return;
	}

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

}

void UTankMovementComponent::IntendMoveForeward(float Throw) {
	UE_LOG(LogTemp, Warning, TEXT("Intend move foreward Throw: %f"), Throw);

	// TODO Prevent double speed from stick + shoulders
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}



