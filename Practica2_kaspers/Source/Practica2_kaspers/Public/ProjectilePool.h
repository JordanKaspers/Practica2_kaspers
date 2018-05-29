// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectilePool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRACTICA2_KASPERS_API UProjectilePool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProjectilePool();

  class AProjectile* Checkout();

  void Return(class AProjectile* ProjectileToReturn);

  void Add(class AProjectile* ProjectileToAdd);
	
};
