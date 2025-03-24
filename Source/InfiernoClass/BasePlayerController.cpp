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
        if (IA_Gamepad_FaceButton_Bottom)
        {
            EnhancedInput->BindAction(IA_Gamepad_FaceButton_Bottom, ETriggerEvent::Triggered, this, &ABasePlayerController::HandleGamePadFaceButtonBottom);
        }
        if (IA_Gamepad_FaceButton_Left)
        {
            EnhancedInput->BindAction(IA_Gamepad_FaceButton_Left, ETriggerEvent::Triggered, this, &ABasePlayerController::HandleGamePadFaceButtonLeft);
        }
        if (IA_Gamepad_FaceButton_Right)
        {
            EnhancedInput->BindAction(IA_Gamepad_FaceButton_Right, ETriggerEvent::Triggered, this, &ABasePlayerController::HandleGamePadFaceButtonRight);
        }
        if (IA_Gamepad_FaceButton_Top)
        {
            EnhancedInput->BindAction(IA_Gamepad_FaceButton_Top, ETriggerEvent::Triggered, this, &ABasePlayerController::HandleGamePadFaceButtonTop);
        }
        if (IA_Gamepad_LeftShoulder)
        {
            EnhancedInput->BindAction(IA_Gamepad_LeftShoulder, ETriggerEvent::Triggered, this, &ABasePlayerController::HandleGamePadLeftShoulder);
        }
        if (IA_Gamepad_RightShoulder)
        {
            EnhancedInput->BindAction(IA_Gamepad_RightShoulder, ETriggerEvent::Triggered, this, &ABasePlayerController::HandleGamePadRightShoulder);
        }
        if (IA_Gamepad_LeftTrigger)
        {
            EnhancedInput->BindAction(IA_Gamepad_LeftTrigger, ETriggerEvent::Triggered, this, &ABasePlayerController::HandleGamePadLeftTrigger);
        }
        if (IA_Gamepad_RightTrigger)
        {
            EnhancedInput->BindAction(IA_Gamepad_RightTrigger, ETriggerEvent::Triggered, this, &ABasePlayerController::HandleGamePadRightTrigger);
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
            MyCharacter->AttackAction(Value);
        }
    }
}

void ABasePlayerController::HandleGamePadFaceButtonBottom(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(ControlledPawn);
        if (MyCharacter)
        {
            MyCharacter->GamePadFaceButtonBottomAction(Value);
        }
    }
}

void ABasePlayerController::HandleGamePadFaceButtonRight(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(ControlledPawn);
        if (MyCharacter)
        {
            MyCharacter->GamePadFaceButtonRightAction(Value);
        }
    }
}

void ABasePlayerController::HandleGamePadFaceButtonLeft(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(ControlledPawn);
        if (MyCharacter)
        {
            MyCharacter->GamePadFaceButtonLeftAction(Value);
        }
    }
}

void ABasePlayerController::HandleGamePadFaceButtonTop(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(ControlledPawn);
        if (MyCharacter)
        {
            MyCharacter->GamePadFaceButtonTopAction(Value);
        }
    }
}

void ABasePlayerController::HandleGamePadLeftShoulder(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(ControlledPawn);
        if (MyCharacter)
        {
            MyCharacter->GamePadLeftShoulderAction(Value);
        }
    }
}

void ABasePlayerController::HandleGamePadRightShoulder(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(ControlledPawn);
        if (MyCharacter)
        {
            MyCharacter->GamePadRightShoulderAction(Value);
        }
    }
}

void ABasePlayerController::HandleGamePadLeftTrigger(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(ControlledPawn);
        if (MyCharacter)
        {
            MyCharacter->GamePadLeftTriggerAction(Value);
        }
    }
}

void ABasePlayerController::HandleGamePadRightTrigger(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(ControlledPawn);
        if (MyCharacter)
        {
            MyCharacter->GamePadRightTriggerAction(Value);
        }
    }
}
