// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Practica2_kaspersGameMode.h"
#include "Practica2_kaspersCharacter.h"
#include "UObject/ConstructorHelpers.h"


APractica2_kaspersGameMode::APractica2_kaspersGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}


