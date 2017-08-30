// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force and to apply forces to the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANK_GAME_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	UTankTrack();

	void ApplySidewaysForce();
	void DriveTrack();
	
private:

	// Max force per track (In Newtons)
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000; // Assume 40 tonne tank, 1g acceleration

	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor,
		UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult &Hit);

	virtual void BeginPlay() override;
	
	float CurrentThrottle = 0;
	
};
