// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectilePool.h"
#include "Projectile.h"


// Sets default values for this component's properties
UProjectilePool::UProjectilePool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AProjectile* UProjectilePool::Checkout()
{
  //UE_LOG(LogTemp, Warning, TEXT(" %s Checkout."), *GetName());
  if (Pool.Num() <= 0)
  {
    //UE_LOG(LogTemp, Warning, TEXT(" %s returned NULLPTR!"), *GetName());
    return nullptr;
  }
  return Pool.Pop();
}

void UProjectilePool:: Return(AProjectile* ProjectileToReturn)
{
  Add(ProjectileToReturn);
}

void UProjectilePool::Add(AProjectile* ProjectileToAdd)
{
  if (ProjectileToAdd == nullptr)
  {
    //UE_LOG(LogTemp, Warning, TEXT(" %s added NULLPTR"), *GetName());
    return;
  }
  Pool.Push(ProjectileToAdd);
  //UE_LOG(LogTemp, Warning, TEXT(" %s added: %s "), *GetName(), *ProjectileToAdd->GetName());
}



