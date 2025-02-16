// Copyright Epic Games, Inc. All Rights Reserved.

#include "SZGJXGameMode.h"
#include "SZGJXHUD.h"
#include "SZGJXCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASZGJXGameMode::ASZGJXGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ASZGJXHUD::StaticClass();
}
