// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UMM_L03GameMode.h"
#include "UMM_L03Character.h"
#include "UObject/ConstructorHelpers.h"

AUMM_L03GameMode::AUMM_L03GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BP/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
