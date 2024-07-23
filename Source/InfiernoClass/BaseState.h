// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
//#include "BaseCharacter.h"
#include "BaseState.generated.h"


class ABaseCharacter;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBaseState : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INFIERNOCLASS_API IBaseState
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    virtual void Enter(ABaseCharacter* Character) = 0;
    virtual void Exit(ABaseCharacter* Character) = 0;

    virtual void Update(ABaseCharacter* Character, float DeltaTime) = 0;

    virtual void HandleInput(ABaseCharacter* Character, FKey Key) = 0;
};
