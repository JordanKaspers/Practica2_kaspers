// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TurretAimingComponent.generated.h"


UENUM()
enum class EFiringState : uint8
{
  Reloading,
  Aiming,
  Locked
};

// Forward Declarations
class UTurretBarrel;
class UTurretDome;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRACTICA2_KASPERS_API UTurretAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

  UFUNCTION(BlueprintCallable, Category = "Setup")
  void Initialise(UTurretBarrel* BarrelToSet, UTurretDome* DomeToSet);

  void AimAt(FVector HitLocation);

  UFUNCTION(BlueprintCallable, Category = "Firing")
  void Fire();

  EFiringState GetFiringState() const;

  // How far can the turret shoot
  UPROPERTY(EditDefaultsOnly, Category = "Setup")
  float ShootingDistance = 1000;

protected:

  UPROPERTY(BlueprintReadOnly, Category = "State")
  EFiringState FiringState = EFiringState::Reloading;

private:

  // Sets default values for this component's properties
  UTurretAimingComponent();

  virtual void BeginPlay() override;

  virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

  void MoveBarrelTowards(FVector AimDirection);

  bool IsBarrelMoving();

  UTurretBarrel* Barrel = nullptr;
  UTurretDome* Turret = nullptr;

  UPROPERTY(EditDefaultsOnly, Category = "Setup")
  TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

  UPROPERTY(EditDefaultsOnly, CAtegory = "Firing")
  float LaunchSpeed = 4000.0f;

  UPROPERTY(EditDefaultsOnly, Category = "Firing")
  float ReloadTimeInSeconds = 0.5f;

  double LastFireTime = 0;

  FVector AimDirection;
};
