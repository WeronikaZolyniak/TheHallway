// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheHallwayGameMode.h"
#include "TheHallwayCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATheHallwayGameMode::ATheHallwayGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
