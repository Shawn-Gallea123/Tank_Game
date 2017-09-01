// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeath);

UCLASS()
class TANK_GAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

	// called by the engine when damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	FDeath OnDeath;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = StartingHealth;

};
