// Copyright Epic Games, Inc. All Rights Reserved.

#include "EromSoftGameMode.h"
#include "EromSoftCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEromSoftGameMode::AEromSoftGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
