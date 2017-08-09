// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAiController.generated.h"

/**
 * 
 */
UCLASS()
class TANK_GAME_API ATankAiController : public AAIController
{
	GENERATED_BODY()
	
	
private:
	void BeginPlay() override;
	ATank *GetControlledTank() const;
	ATank *GetPlayerTank() const;
	
	
};
