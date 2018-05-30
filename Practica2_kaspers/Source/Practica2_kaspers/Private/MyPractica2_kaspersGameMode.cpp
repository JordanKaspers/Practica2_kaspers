// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPractica2_kaspersGameMode.h"
#include "Projectile.h"
#include "EngineUtils.h"
#include "ProjectilePool.h"
#include "Projectile.h"


AMyPractica2_kaspersGameMode::AMyPractica2_kaspersGameMode()
{
  ProjectilePool = CreateDefaultSubobject<UProjectilePool>(FName("Projectile Pool"));
  InactiveProjectileStorage = FVector(0, 0, 1000);
}

UProjectilePool* AMyPractica2_kaspersGameMode::GetPool()
{
  if (ProjectilePool == nullptr)
  {
    UE_LOG(LogTemp, Warning, TEXT(" %s returned NULLPTR!"), *GetName());
  }
  return ProjectilePool;
}

void AMyPractica2_kaspersGameMode::PopulateProjectilePool()
{
  TActorIterator<AProjectile> ProjectileIterator = TActorIterator<AProjectile>(GetWorld());
  
  while (ProjectileIterator)
  {
    //AProjectile* FoundProjectile = *ProjectileIterator;
    AddToPool(*ProjectileIterator);
    ++ProjectileIterator;
  }
}

void AMyPractica2_kaspersGameMode::AddToPool(AProjectile *ProjectileToAdd)
{
  //UE_LOG(LogTemp, Warning, TEXT("Adding Projectile: %s to Pool"), *ProjectileToAdd->GetName());
  ProjectilePool->Add(ProjectileToAdd);
}

