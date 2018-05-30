// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "MyPractica2_kaspersGameMode.h"
#include "ProjectilePool.h"


// Sets default values
AProjectile::AProjectile()
{
  // Using sphere collision
  CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
  CollisionComp->InitSphereRadius(5.0f);
  CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
  CollisionComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);		// set up a notification for when this component hits something blocking

  // Players can't walk on it
  CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
  CollisionComp->CanCharacterStepUpOn = ECB_No;

  // Set as root component
  RootComponent = CollisionComp;

  // Using a ProjectileMovementComponent for movement
  ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
  ProjectileMovement->UpdatedComponent = CollisionComp;
  ProjectileMovement->InitialSpeed = 4000.f;
  ProjectileMovement->MaxSpeed = 4000;
  ProjectileMovement->bRotationFollowsVelocity = true;
  ProjectileMovement->bShouldBounce = true;
  //ProjectileMovement->Deactivate();
  //ProjectileMovement->Activate();

  // Die after 3 seconds by default
  InitialLifeSpan = 3.0f;

  if (GetWorld()) {
    MyGameMode = (AMyPractica2_kaspersGameMode*)GetWorld()->GetAuthGameMode();
  }
}

void AProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
  //UE_LOG(LogTemp, Warning, TEXT(" %s EndPlay "), *GetName())
  bEndPlay = true;
  //ProjectileMovement->Deactivate();
  if (MyGameMode != nullptr)
  {
    MyGameMode->GetPool()->Return(this);
  }
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
  // Only add impulse if we hit a physics
  if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
  {
    OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
    //Destroy();
  }
}

void AProjectile::LaunchProjectile(float Speed)
{
  ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
  ProjectileMovement->Activate();
  
}
