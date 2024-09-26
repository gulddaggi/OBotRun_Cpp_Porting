// Copyright Epic Games, Inc. All Rights Reserved.

#include "OBotRun_Cpp_PortingGameMode.h"
#include "OBotRun_Cpp_PortingCharacter.h"
#include "UObject/ConstructorHelpers.h"

AOBotRun_Cpp_PortingGameMode::AOBotRun_Cpp_PortingGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
