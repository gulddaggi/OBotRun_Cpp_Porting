// Fill out your copyright notice in the Description page of Project Settings.


#include "OBRMainGameMode.h"
#include "OBRCharacter.h"

AOBRMainGameMode::AOBRMainGameMode()
{
	DefaultPawnClass = AOBRCharacter::StaticClass();
}
