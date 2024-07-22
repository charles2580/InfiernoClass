// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
//#include "BaseCharacter.h"
#include "BaseState.generated.h"


class MyCharacter;
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
    virtual void Enter(MyCharacter* Character) = 0;
    virtual void Exit(MyCharacter* Character) = 0;

    virtual void Update(MyCharacter* Character, float DeltaTime) = 0;

    virtual void HandleInput(MyCharacter* Character, FKey Key) = 0;
};
