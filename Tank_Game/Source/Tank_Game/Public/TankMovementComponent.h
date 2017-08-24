// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 *  Responsible for driving Tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANK_GAME_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	// Throw is the -1 - +1 value given by the left thumbstick
	// indicating how fast the Tank is intended to go
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForeward(float Throw);

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet);

	// TODO: Check best privacy
	virtual void RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTankTrack *LeftTrack = nullptr;
	UTankTrack *RightTrack = nullptr;
	
};
