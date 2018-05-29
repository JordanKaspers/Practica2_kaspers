// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"
#include "ProjectilePool.h"
#include "Projectile.h"


// Sets default values
ATurret::ATurret()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
  
}
/*
// Called to bind functionality to input
void ATurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
*/

UProjectilePool* ATurret::GetPool()
{
  return Pool;
}

void ATurret::SetPool(UProjectilePool* InPool)
{
  UE_LOG(LogTemp, Warning, TEXT(" %s -> Setting Pool %s "), *(this->GetName()), *(InPool->GetName()));
  Pool = InPool;

  PositionProjectile();
}

void ATurret::PositionProjectile()
{
  AProjectile* Projectile = Pool->Checkout();
  if (Projectile == nullptr)
  {
    UE_LOG(LogTemp, Error, TEXT("Not enough projectiles in pool!"));
    return;
  }
  Projectile->SetActorLocation(GetActorLocation());
}
