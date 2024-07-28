// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseState.h"
#include "WalkState.generated.h"

/**
 * 
 */
UCLASS()
class INFIERNOCLASS_API UWalkState : public UObject, public IBaseState
{
	GENERATED_BODY()

public:

    virtual void Enter(ABaseCharacter* Character) override;
    virtual void Exit(ABaseCharacter* Character) override;

    virtual void Update(ABaseCharacter* Character, float DeltaTime) override;

    virtual void HandleInput(ABaseCharacter* Character, FKey Key) override;
};
