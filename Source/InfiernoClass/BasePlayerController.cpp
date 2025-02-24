// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "BaseCharacter.h"
#include "GameFramework/Pawn.h"
#include "Engine/LocalPlayer.h"

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

    {
        FInputModeGameAndUI InputMode;
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        SetInputMode(InputMode);
    }

    ULocalPlayer* LocalPlayer = GetLocalPlayer();
    if (LocalPlayer)
    {
        if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
        {
            // LocalPlayer의 ControllerId를 확인하여 각기 다른 Mapping Context를 할당합니다.
            int32 PlayerIndex = LocalPlayer->GetLocalPlayerIndex();
            UE_LOG(LogTemp, Log, TEXT("LocalPlayer Index: %d"), PlayerIndex);

            if (PlayerIndex == 0 && MappingContext_Player1)
            {
                InputSubsystem->AddMappingContext(MappingContext_Player1, 1);
                UE_LOG(LogTemp, Log, TEXT("MappingContext_Player1 added for ControllerId 0"));
            }
            else if (PlayerIndex == 1 && MappingContext_Player2)
            {
                InputSubsystem->AddMappingContext(MappingContext_Player2, 1);
                UE_LOG(LogTemp, Log, TEXT("MappingContext_Player2 added for ControllerId 1"));
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("MappingContext not added. ControllerId: %d"), PlayerIndex);
            }
        }
    }
}

void ABasePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
    {
        if (IA_Move)
        {
            EnhancedInput->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ABasePlayerController::HandleMove);
        }
        if (IA_Jump)
        {
            EnhancedInput->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ABasePlayerController::HandleJump);
        }
        if (IA_Attack)
        {
            EnhancedInput->BindAction(IA_Attack, ETriggerEvent::Triggered, this, &ABasePlayerController::HandleAttack);
        }
    }
}

void ABasePlayerController::HandleMove(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(ControlledPawn);
        if (MyCharacter)
        {
            MyCharacter->MoveAction(Value);
        }
    }
}

void ABasePlayerController::HandleJump(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(ControlledPawn);
        if (MyCharacter)
        {
            MyCharacter->JumpAction(Value);
        }
    }
}

void ABasePlayerController::HandleAttack(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(ControlledPawn);
        if (MyCharacter)
        {
            //MyCharacter->AttackAction(Value);
        }
    }
}
