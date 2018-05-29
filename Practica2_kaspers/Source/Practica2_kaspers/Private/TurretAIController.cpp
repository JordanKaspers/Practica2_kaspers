// Fill out your copyright notice in the Description page of Project Settings.

#include "TurretAIController.h"
#include "GameFramework/PlayerController.h"
#include "TurretAimingComponent.h"
#include "Turret.h"


void ATurretAIController::BeginPlay()
{
  Super::BeginPlay();
}

void ATurretAIController::SetPawn(APawn* InPawn)
{
  Super::SetPawn(InPawn);
  if (InPawn)
  {
    ATurret* PossessedTurret = Cast<ATurret>(InPawn);
    //if (!ensure(PossessedTurret)) { return; }
    if (!PossessedTurret) { return; }

    // Subscribe method to the turret's death event
    PossessedTurret->OnDeath.AddUniqueDynamic(this, &ATurretAIController::OnPossessedTurretDeath);
  }
}

void ATurretAIController::OnPossessedTurretDeath()
{
  if (!GetPawn()) { return; }
  GetPawn()->DetachFromControllerPendingDestroy();
}

void ATurretAIController::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  APawn* Player = GetWorld()->GetFirstPlayerController()->GetPawn();
  APawn* ControlledTurret = GetPawn();

  if (!ensure(Player && ControlledTurret)) { return; }
  // Move towards the player
  //MoveToActor(Player, AcceptanceRadius);   

  // Aim towards the player
  UTurretAimingComponent* AimingComponent = ControlledTurret->FindComponentByClass<UTurretAimingComponent>();
  AimingComponent->AimAt(Player->GetActorLocation());

  if (AimingComponent->GetFiringState() == EFiringState::Locked)
  {
    if (ControlledTurret->GetDistanceTo(Player) < AimingComponent->ShootingDistance)
    {
      AimingComponent->Fire();
    }
  }
}



