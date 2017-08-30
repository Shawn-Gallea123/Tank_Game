// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAiController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class TANK_GAME_API ATankAiController : public AAIController
{
	GENERATED_BODY()
	
protected:
	// How close can the AI Tank get
	UPROPERTY(EditDefaultsOnly)
	float AcceptanceRadius = 8000.f;
	
private:
	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
};
