// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet) {
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	// UE_LOG(LogTemp, Warning, TEXT("Intend move foreward Throw: %f"), Throw);

	if (!ensure(LeftTrack && RightTrack)) {
		return;
	}

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {

	if (!ensure(LeftTrack && RightTrack)) {
		return;
	}

	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed) {
	// Don't want to call Super, are overriding

	// where the Tank is currently facing
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	// where the AI pathfinder wants the Tank to be moving and facing
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(AIForwardIntention, TankForward);
	IntendMoveForward(ForwardThrow);

	auto RotationThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(RotationThrow);

	// UE_LOG(LogTemp, Warning, TEXT("%s RequestDirectMove, MoveVelocity: %s"), *TankName, *AIForwardIntention);
}



