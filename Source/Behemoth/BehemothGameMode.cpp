// Copyright Epic Games, Inc. All Rights Reserved.

#include "BehemothGameMode.h"
#include "BehemothCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABehemothGameMode::ABehemothGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
