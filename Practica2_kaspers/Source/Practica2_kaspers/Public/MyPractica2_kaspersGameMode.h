// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Practica2_kaspersGameMode.h"
#include "MyPractica2_kaspersGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICA2_KASPERS_API AMyPractica2_kaspersGameMode : public APractica2_kaspersGameMode
{
	GENERATED_BODY()
	
public:

  AMyPractica2_kaspersGameMode();

  UFUNCTION(BlueprintCallable, Category = "Pool")
  void PopulateProjectilePool();

  UFUNCTION(BlueprintCallable, Category = "Pool")
  class UProjectilePool* GetPool();

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pool")
  class UProjectilePool* ProjectilePool;

private:

  void AddToPool(class AProjectile *ProjectileToAdd);
	
	
};
