// Fill out your copyright notice in the Description page of Project Settings.


#include "IdleState.h"
#include "BaseCharacter.h"

void UIdleState::Enter(ABaseCharacter* Character)
{
	Character->Speed = 0.0f;
	UE_LOG(LogTemp, Warning, TEXT("Enter IdleState"));
}

void UIdleState::Exit(ABaseCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("Exit IdleState"));
}

void UIdleState::Update(ABaseCharacter* Character, float DeltaTime)
{
	if (Character->GetVelocity().Size() > 0)
	{
		Character->RequestStateChange(ECharacterState::Walking);
	}
}

void UIdleState::HandleInput(ABaseCharacter* Character, FKey Key)
{
}
