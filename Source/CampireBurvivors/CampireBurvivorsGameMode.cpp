// Copyright Epic Games, Inc. All Rights Reserved.

#include "CampireBurvivorsGameMode.h"
#include "CampireBurvivorsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACampireBurvivorsGameMode::ACampireBurvivorsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
