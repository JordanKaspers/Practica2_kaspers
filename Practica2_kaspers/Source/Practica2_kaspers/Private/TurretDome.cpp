// Fill out your copyright notice in the Description page of Project Settings.

#include "TurretDome.h"


void UTurretDome::Rotate(float RelativeSpeed)
{
  RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);
  auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
  auto Rotation = RelativeRotation.Yaw + RotationChange;
  SetRelativeRotation(FRotator(0, Rotation, 0));
}

