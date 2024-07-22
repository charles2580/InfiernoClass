// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseState.h"
#include "HitState.generated.h"

/**
 * 
 */
UCLASS()
class INFIERNOCLASS_API UHitState : public UObject, public IBaseState
{
	GENERATED_BODY()
    
public:

    virtual void Enter(MyCharacter* Character) override;
    virtual void Exit(MyCharacter* Character) override;

    virtual void Update(MyCharacter* Character, float DeltaTime) override;

    virtual void HandleInput(MyCharacter* Character, FKey Key) override;
};
