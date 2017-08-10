// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // must be last include

/**
 * 
 */
UCLASS()
class TANK_GAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	ATank *GetControlledTank() const;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Start the tank moving the barrel towards the spot where
	// the crosshair intersects the world
	void AimTowardsCrosshair();
	
};
