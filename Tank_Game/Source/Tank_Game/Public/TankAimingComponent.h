// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked
};

class AProjectile;
class UTankBarrel;
class UTankTurret;

// Holds Barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANK_GAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent(); 

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void FireCannon();

protected:

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

public:	

	void AimAt(FVector HitLocation);
		
private:
	UTankBarrel *Barrel = nullptr;
	UTankTurret *Turret = nullptr;
	void MoveBarrel(FVector AimDirection);

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickfunction) override;

	void BeginPlay() override;

	bool IsBarrelMoving();

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.0;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	double LastFireTime = 0.0;

	FVector AimingDirection;
	
};
