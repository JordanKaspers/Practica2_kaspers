// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "ActivatableMesh.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActivateEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRACTICA2_KASPERS_API UActivatableMesh : public UActorComponent
{
	GENERATED_BODY()

public:
  // Sets default values for this component's properties
  UActivatableMesh();

protected:
  // Called when the game starts
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

  UPROPERTY(BlueprintAssignable)
  FActivateEvent OnActivated;

  UPROPERTY(BlueprintAssignable)
  FActivateEvent OnDeactivated;

private:

  UPROPERTY(EditAnywhere)
  ATriggerVolume* VolumeToActivate = nullptr;

  UPROPERTY(EditAnywhere)
  float MassToActivate = 250.0f;

  UPROPERTY(EditAnywhere)
  float TimeBeforeDeactivation = 5.0f;

  float TimeActivated = 0.0f;

  float TimeDeactivated = 0.0f;

  float TimeInSeconds = 0.0f;

  UFUNCTION(BlueprintCallable, Category = "Setup")
  float GetMassInVolume();
};
