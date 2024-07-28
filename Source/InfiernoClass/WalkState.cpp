// Fill out your copyright notice in the Description page of Project Settings.


#include "WalkState.h"
#include "BaseCharacter.h"

void UWalkState::Enter(ABaseCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("Enter WalkState"));
}

void UWalkState::Exit(ABaseCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("Exit WalkState"));
}

void UWalkState::Update(ABaseCharacter* Character, float DeltaTime)
{
	if (Character->GetVelocity().Size() == 0)
	{
		Character->RequestStateChange(ECharacterState::Idle);
	}
}

void UWalkState::HandleInput(ABaseCharacter* Character, FKey Key)
{
}
