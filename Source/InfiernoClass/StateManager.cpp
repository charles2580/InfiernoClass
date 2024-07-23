// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "StateManager.h"

void UStateManager::Initialize(ABaseCharacter* MyCharacter)
{
	player = MyCharacter;
}

void UStateManager::ChangeState(TSubclassOf<UObject> NewStateClass)
{
    if (player && player->CurrentState)
    {
        player->CurrentState->Exit(player);
    }

    player->CurrentState = NewObject<UObject>(player, NewStateClass);
    if (player->CurrentState)
    {
        player->CurrentState->Enter(player);
    }
}
