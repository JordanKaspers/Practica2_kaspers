// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TurretAIController.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICA2_KASPERS_API ATurretAIController : public AAIController
{
	GENERATED_BODY()
	
public:

  virtual void BeginPlay() override;

  virtual void Tick(float DeltaTime) override;

protected:

  // How close can the turret get
  UPROPERTY(EditDefaultsOnly, Category = "Setup")
  float AcceptanceRadius = 0;

private:

  virtual void SetPawn(APawn* InPawn) override;

  UFUNCTION()
  void OnPossessedTurretDeath();
	
	
};
