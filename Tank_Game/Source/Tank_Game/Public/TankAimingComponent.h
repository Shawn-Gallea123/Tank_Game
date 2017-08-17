// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Holds Barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANK_GAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent(); 

	void SetBarrelReference(UTankBarrel *BarrelToSet);

protected:

public:	

	void AimAt(FVector HitLocation, float LaunchSpeed);
		
private:
	UTankBarrel *Barrel = nullptr;
	void MoveBarrel(FVector AimDirection);
	
};
