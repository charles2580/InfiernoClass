// Copyright Epic Games, Inc. All Rights Reserved.


#include "InfiernoClassGameModeBase.h"

AInfiernoClassGameModeBase::AInfiernoClassGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnBPClass(TEXT("/Game/Models/Characters/TestMonkey"));
	if (DefaultPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = DefaultPawnBPClass.Class;
	}
}
