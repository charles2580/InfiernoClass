// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseState.h"
#include "StateManager.generated.h"

class ABaseCharacter;

/**
 * 
 */
UCLASS()
class INFIERNOCLASS_API UStateManager : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(ABaseCharacter* MyCharacter);
	void ChangeState(TSubclassOf<UObject> NewStateClass);

private:
	ABaseCharacter* player;
};
