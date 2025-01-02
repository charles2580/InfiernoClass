// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseCharacter.h"
#include "InfiernoClassGameModeBase.generated.h"

UCLASS()
class INFIERNOCLASS_API AInfiernoClassGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	AInfiernoClassGameModeBase();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Player References");
	ABaseCharacter* Player1;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Player References");
	ABaseCharacter* Player2;
};
