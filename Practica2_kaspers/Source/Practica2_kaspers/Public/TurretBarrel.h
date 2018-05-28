// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TurretBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class PRACTICA2_KASPERS_API UTurretBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

  //  -1 is max downward speed, and +1 is max up movement
  void Elevate(float RelativeSpeed);

private:

  UPROPERTY(EditDefaultsOnly, Category = "Setup")
  float MaxDegreesPerSecond = 7.5f;

  UPROPERTY(EditDefaultsOnly, Category = "Setup")
  float MaxElevationDegrees = 40.0f;

  UPROPERTY(EditDefaultsOnly, Category = "Setup")
  float MinElevationDegrees = 0.0f;
	
	
};
