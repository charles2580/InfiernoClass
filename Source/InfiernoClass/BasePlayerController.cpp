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
            EnhancedInput->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ABasePlayerController::HandleMoveInput);
        }
        if (IA_Jump)
        {
            EnhancedInput->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ABasePlayerController::HandleJumpInput);
        }
        if (IA_Attack)
        {
            EnhancedInput->BindAction(IA_Attack, ETriggerEvent::Triggered, this, &ABasePlayerController::HandleAttackInput);
        }
        if (IA_Forward)
        {
            EnhancedInput->BindAction(IA_Forward, ETriggerEvent::Triggered, this, &ABasePlayerController::HandleForwardInput);
        }
        if (IA_Backward)
        {
            EnhancedInput->BindAction(IA_Backward, ETriggerEvent::Triggered, this, &ABasePlayerController::HandleBackwardInput);
        }
        if (IA_Crunch)
        {
            EnhancedInput->BindAction(IA_Crunch, ETriggerEvent::Triggered, this, &ABasePlayerController::HandleCrunchInput);
        }
        if (IA_CrunchReleased)
        {
            EnhancedInput->BindAction(IA_CrunchReleased, ETriggerEvent::Triggered, this, &ABasePlayerController::HandleCrunchReleasedInput);
        }
        if (IA_LeftPunch)
        {
            EnhancedInput->BindAction(IA_LeftPunch, ETriggerEvent::Triggered, this, &ABasePlayerController::HandleLeftPunchInput);
        }
        if (IA_RightPunch)
        {
            EnhancedInput->BindAction(IA_RightPunch, ETriggerEvent::Triggered, this, &ABasePlayerController::HandleRightPunchInput);
        }
        if (IA_LeftKick)
        {
            EnhancedInput->BindAction(IA_LeftKick, ETriggerEvent::Triggered, this, &ABasePlayerController::HandleLeftKickInput);
        }
        if (IA_RightKick)
        {
            EnhancedInput->BindAction(IA_RightKick, ETriggerEvent::Triggered, this, &ABasePlayerController::HandleRightKickInput);
        }
        if (IA_AnyKey)
        {
            EnhancedInput->BindAction(IA_AnyKey, ETriggerEvent::Triggered, this, &ABasePlayerController::HandleRemoveInputFromInputBuffer);
        }
    }
}

void ABasePlayerController::HandleMoveInput(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(ControlledPawn);
        if (MyCharacter)
        {
            MyCharacter->MoveAction(Value);
        }
    }
    //FEnhancedActionKeyMapping
}

void ABasePlayerController::HandleJumpInput(const FInputActionValue& Value)
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

void ABasePlayerController::HandleAttackInput(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(ControlledPawn);
        if (MyCharacter)
        {
            MyCharacter->AttackAction(Value);
        }
    }
}

void ABasePlayerController::HandleForwardInput(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(ControlledPawn);
        if (MyCharacter)
        {
            MyCharacter->ForwardAction(Value);
        }
    }
}

void ABasePlayerController::HandleBackwardInput(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(ControlledPawn);
        if (MyCharacter)
        {
            MyCharacter->BackwardAction(Value);
        }
    }
}

void ABasePlayerController::HandleCrunchInput(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(ControlledPawn);
        if (MyCharacter)
        {
            MyCharacter->CrunchAction(Value);
        }
    }
}

void ABasePlayerController::HandleCrunchReleasedInput(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(ControlledPawn);
        if (MyCharacter)
        {
            MyCharacter->CrunchReleased(Value);
        }
    }
}

void ABasePlayerController::HandleLeftPunchInput(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(ControlledPawn);
        if (MyCharacter)
        {
            MyCharacter->LeftPunchAction(Value);
        }
    }
}

void ABasePlayerController::HandleRightPunchInput(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(ControlledPawn);
        if (MyCharacter)
        {
            MyCharacter->RightPunchAction(Value);
        }
    }
}

void ABasePlayerController::HandleLeftKickInput(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(ControlledPawn);
        if (MyCharacter)
        {
            MyCharacter->LeftKickAction(Value);
        }
    }
}

void ABasePlayerController::HandleRightKickInput(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(ControlledPawn);
        if (MyCharacter)
        {
            MyCharacter->RightKickAction(Value);
        }
    }
}

void ABasePlayerController::HandleRemoveInputFromInputBuffer(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(ControlledPawn);
        if (MyCharacter)
        {
            MyCharacter->RemoveInputFromInputBuffer();
        }
    }
}
