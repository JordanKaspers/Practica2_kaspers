// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Practica2_kaspersCharacter.generated.h"

UCLASS(config=Game)
class APractica2_kaspersCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:

	APractica2_kaspersCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
  /*
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Set up")
  bool Running = false;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Set up")
  bool Throwing = false;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Set up")
  bool Sneaking = false;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Set up")
  bool Crouching = false;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Set up")
  float Speed = 0;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Set up")
  float MaxWalkSpeed = 200;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Set up")
  float SneakSpeed = 25;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Set up")
  float CrouchSpeed = 150;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Set up")
  float RunSpeed = 400;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Set up")
  float CrouchVolume = 0.25f;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Set up")
  float RunVolume = 1;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Set up")
  float SoundRadius = 100;
  */
protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

protected:

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

