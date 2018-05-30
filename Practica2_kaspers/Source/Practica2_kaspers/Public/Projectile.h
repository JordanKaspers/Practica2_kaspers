// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class PRACTICA2_KASPERS_API AProjectile : public AActor
{
	GENERATED_BODY()

  /** Sphere collision component */
  UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
  class USphereComponent* CollisionComp;

  /** Projectile movement component */
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
  class UProjectileMovementComponent* ProjectileMovement;

public:	
	
	// Sets default values for this actor's properties
	AProjectile();

  virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

  /** called when projectile hits something */
  UFUNCTION()
  void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

  /** Returns CollisionComp subobject **/
  FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
  /** Returns ProjectileMovement subobject **/
  FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
  
  UFUNCTION(BlueprintCallable, Category = "Projectile")
  void LaunchProjectile(float Speed);

  bool bEndPlay = false;

  class AMyPractica2_kaspersGameMode* MyGameMode;
};
