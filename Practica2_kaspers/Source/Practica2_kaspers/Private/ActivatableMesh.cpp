// Fill out your copyright notice in the Description page of Project Settings.

#include "ActivatableMesh.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UActivatableMesh::UActivatableMesh()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActivatableMesh::BeginPlay()
{
	Super::BeginPlay();
  if (!VolumeToActivate)
  {
    UE_LOG(LogTemp, Error, TEXT("%s missing TriggerVolume!"), *GetOwner()->GetName());
  }
}


// Called every frame
void UActivatableMesh::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
  // Poll the Trigger Volume
  if (GetMassInVolume() >= MassToActivate)
  {
    TimeActivated = UGameplayStatics::GetRealTimeSeconds(GetWorld());
    //UE_LOG(LogTemp, Warning, TEXT("TimeActivated: %f"), TimeActivated);
    OnActivated.Broadcast();
  }
  else
  {
    TimeDeactivated = UGameplayStatics::GetRealTimeSeconds(GetWorld());
    //UE_LOG(LogTemp, Warning, TEXT("TimeDeactivated: %f"), TimeDeactivated);
    if (TimeActivated + TimeBeforeDeactivation < TimeDeactivated)
    {
      OnDeactivated.Broadcast();
    }
  }
}

float UActivatableMesh::GetMassInVolume()
{
  float Mass = 0.0f;

  // Find all the overlapping actors
  TArray<AActor*> ActorsInVolume;
  if (!VolumeToActivate) { return Mass; }
  VolumeToActivate->GetOverlappingActors(ActorsInVolume);
  // Iterate through them adding their masses
  for (const auto* Actor : ActorsInVolume)
  {
    //Mass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
    if (Actor->ActorHasTag(TEXT("Player")) || Actor->ActorHasTag(TEXT("Enemy")))
    {
      Mass = 1000;
    }
    else if (Actor->ActorHasTag(TEXT("Projectile")))
    {
      Mass = 100;
    }
    //UE_LOG(LogTemp, Warning, TEXT("%s is in trigger volume"), *Actor->GetName());
  }
  //UE_LOG(LogTemp, Warning, TEXT("%f is in trigger volume"), Mass);
  return Mass;
}

