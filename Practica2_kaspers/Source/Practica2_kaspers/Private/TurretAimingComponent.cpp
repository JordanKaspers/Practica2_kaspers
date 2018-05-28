// Fill out your copyright notice in the Description page of Project Settings.

#include "TurretAimingComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TurretBarrel.h"
#include "TurretDome.h"
#include "Projectile.h"


// Sets default values for this component's properties
UTurretAimingComponent::UTurretAimingComponent()
{
  // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
  // off to improve performance if you don't need them.
  PrimaryComponentTick.bCanEverTick = true;

}

void UTurretAimingComponent::BeginPlay()
{
  // So that first fire is after initial reload
  LastFireTime = FPlatformTime::Seconds();
}

void UTurretAimingComponent::Initialise(UTurretBarrel* BarrelToSet, UTurretDome* DomeToSet)
{
  Barrel = BarrelToSet;
  Turret = DomeToSet;
}

void UTurretAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
  if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
  {
    FiringState = EFiringState::Reloading;
  }
  else if (IsBarrelMoving())
  {
    FiringState = EFiringState::Aiming;
  }
  else
  {
    FiringState = EFiringState::Locked;
  }
}

EFiringState UTurretAimingComponent::GetFiringState() const
{
  return FiringState;
}

bool UTurretAimingComponent::IsBarrelMoving()
{
  if (!ensure(Barrel)) { return false; }
  FVector BarrelForward = Barrel->GetForwardVector();
  return !BarrelForward.Equals(AimDirection, 0.01f);
}

void UTurretAimingComponent::AimAt(FVector HitLocation)
{
  if (!ensure(Barrel)) { return; }

  FVector OutLaunchVelocity;
  FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
  bool HaveAimSolution = (UGameplayStatics::SuggestProjectileVelocity(
    this,
    OutLaunchVelocity,
    StartLocation,
    HitLocation,
    LaunchSpeed,
    false,
    0,
    0,
    ESuggestProjVelocityTraceOption::DoNotTrace));

  if (HaveAimSolution)
  {
    AimDirection = OutLaunchVelocity.GetSafeNormal();
    MoveBarrelTowards(AimDirection);
  }
  //  If no solution found, do nothing
}

void UTurretAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
  if (!ensure(Barrel) || !ensure(Turret)) { return; }
  // Difference between current barrel rotation, and AimDirection
  FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
  FRotator AimAsRotator = AimDirection.Rotation();
  FRotator DeltaRotator = AimAsRotator - BarrelRotator;

  Barrel->Elevate(DeltaRotator.Pitch);
  if (FMath::Abs(DeltaRotator.Yaw) < 180)
  {
    Turret->Rotate(DeltaRotator.Yaw);
  }
  else  // ensuring rotating the fast way around
  {
    Turret->Rotate(-DeltaRotator.Yaw);
  }
}

void UTurretAimingComponent::Fire()
{
  if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
  {
    // Spawn a bullet at the socket location of the barrel
    if (!ensure(Barrel)) { return; }
    if (!ensure(ProjectileBlueprint)) { return; }
    auto Projectile = GetWorld()->SpawnActor<AProjectile>(
      ProjectileBlueprint,
      Barrel->GetSocketLocation(FName("Bullet")),
      Barrel->GetSocketRotation(FName("Bullet"))
      );
    Projectile->LaunchProjectile(LaunchSpeed);
    LastFireTime = FPlatformTime::Seconds();
  }
}