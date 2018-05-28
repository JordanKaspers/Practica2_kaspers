// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TurretDome.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class PRACTICA2_KASPERS_API UTurretDome : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

  // -1 is max downward speed, and +1 is max up movement
  void Rotate(float RelativeSpeed);


private:

  UPROPERTY(EditDefaultsOnly, Category = "Setup")
  float MaxDegreesPerSecond = 25.0f;
	
	
};
