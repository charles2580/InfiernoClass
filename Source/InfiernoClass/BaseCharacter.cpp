// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "IdleState.h"
#include "WalkState.h"
#include "AttackState.h"
#include "HitState.h"
#include "MotionWarpingComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Speed = 0;
    Block = false;
    StateManager = CreateDefaultSubobject<UStateManager>(TEXT("StateManager"));
    movementComponent = GetCharacterMovement();
    
    MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarping"));

    removeInputFromBufferTime = 1.0f;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

    //StateManager->Initialize(this);
    //StateManager->ChangeState(UIdleState::StaticClass());
    animInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    //if (CurrentState)
    //{
    //    CurrentState->Update(this, DeltaTime);
    //}
}

// Called to bind functionality to input
//void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
//    {
//        EnhancedInputComponent->BindAction(IA_MoveForward, ETriggerEvent::Started, this, &ABaseCharacter::MoveStarted);
//        EnhancedInputComponent->BindAction(IA_MoveForward, ETriggerEvent::Completed, this, &ABaseCharacter::MoveCompleted);
//        EnhancedInputComponent->BindAction(IA_MoveForward, ETriggerEvent::Triggered, this, &ABaseCharacter::MoveAction);
//        EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ABaseCharacter::JumpAction);
//        EnhancedInputComponent->BindAction(IA_Crouch, ETriggerEvent::Triggered, this, &ABaseCharacter::CrouchAction);
//     
//    }
//
//}

void ABaseCharacter::RequestStateChange(ECharacterState NewState)
{
    switch (NewState)
    {
    case ECharacterState::Idle:
        StateManager->ChangeState(UIdleState::StaticClass());
        break;
    case ECharacterState::Walking:
        StateManager->ChangeState(UWalkState::StaticClass());
        break;
    case ECharacterState::Attack:
        StateManager->ChangeState(UAttackState::StaticClass());
        break;
    case ECharacterState::Hit:
        StateManager->ChangeState(UHitState::StaticClass());
        break;
    case ECharacterState::Block:
        //StateManager->ChangeState(UHitState::StaticClass());
        break;
    }

}

float ABaseCharacter::GetSpeed() const
{
    return Speed;
}

bool ABaseCharacter::GetBlock() const
{
    return Block;
}

void ABaseCharacter::SetWarpTarget(FName TargetName, const FTransform& TargetTransform)
{
    if (MotionWarpingComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("The MotionWarping is Successed."));
        MotionWarpingComponent->AddOrUpdateWarpTargetFromTransform(TargetName, TargetTransform);
    }
}

void ABaseCharacter::ClearWarpTarget(FName TargetName)
{
    if (MotionWarpingComponent)
    {
        MotionWarpingComponent->RemoveWarpTarget(TargetName);
    }
}

void ABaseCharacter::ApplyDamage(float Damage)
{
    UE_LOG(LogTemp, Warning, TEXT("%s took %.1f damage!"), *GetName(), Damage);
}

bool ABaseCharacter::AddInputToInputBuffer(FInputInfo _inputinfo)
{
    inputBuffer.Add(_inputinfo);

    const float MaxBufferTime = 2.0f;
    const float CurrentTime = GetWorld()->GetTimeSeconds();

    inputBuffer.RemoveAll([CurrentTime, MaxBufferTime](const FInputInfo& Info) {
        return CurrentTime - Info.timeStamp > MaxBufferTime;
        });

    return CheckInputBufferForCommand();
}

void ABaseCharacter::RemoveInputFromInputBuffer()
{
    if (!GetWorld())
    {
        return;
    }

    float CurrentTime = GetWorld()->GetTimeSeconds();

    const float ExpireThreshold = 0.3f;

    for (int i = inputBuffer.Num() - 1; i >= 0; --i)
    {
        if (CurrentTime - inputBuffer[i].timeStamp > ExpireThreshold)
        {
            inputBuffer.RemoveAt(i);
        }
    }
}

bool ABaseCharacter::CheckInputBufferForCommand()
{
    //int correctSequenceCounter = 0;
    //for (auto currentCommand : characterCommands)
    //{
    //    for (int commandInput = 0; commandInput < currentCommand.inputs.Num(); ++commandInput)
    //    {
    //        for (int input = 0; input < inputBuffer.Num(); ++input)
    //        {
    //            if (input + correctSequenceCounter < inputBuffer.Num())
    //            {
    //                if (inputBuffer[input + correctSequenceCounter].inputName.Compare(currentCommand.inputs[commandInput]) == 0)
    //                {
    //                    //UE_LOG(LogTemp, Warning, TEXT("The player added another input to the command sequence"));
    //                    ++correctSequenceCounter;
    //                    if (correctSequenceCounter == currentCommand.inputs.Num())
    //                    {
    //                        StartCommand(currentCommand.name);
    //                    }
    //                    break;
    //                }
    //                else
    //                {
    //                    //UE_LOG(LogTemp, Warning, TEXT("The player borke the command sequence."));
    //                    correctSequenceCounter = 0;
    //                }
    //            }
    //            else
    //            {
    //                //UE_LOG(LogTemp, Warning, TEXT("The player is not yet finished with the command sequence."));
    //                correctSequenceCounter = 0;
    //            }
    //        }
    //    }
    //}
    const float MaxInputDelay = 0.3f;

    for (const auto& Command : characterCommands)
    {
        const int32 CommandLength = Command.inputs.Num();
        const int32 BufferLength = inputBuffer.Num();

        if (BufferLength < CommandLength)
        {
            continue;
        }

        // inputBuffer 전체를 슬라이딩 윈도우 방식으로 순회
        for (int32 i = 0; i <= BufferLength - CommandLength; ++i)
        {
            bool bMatched = true;

            for (int32 j = 0; j < CommandLength; ++j)
            {
                if (inputBuffer[i + j].inputName != Command.inputs[j])
                {
                    bMatched = false;
                    break;
                }

                // 시간 조건 검사 (j > 0 부터)
                if (j > 0)
                {
                    float Delta = inputBuffer[i + j].timeStamp - inputBuffer[i + j - 1].timeStamp;
                    if (Delta > MaxInputDelay)
                    {
                        UE_LOG(LogTemp, Warning, TEXT("Input too slow: %.2f"), Delta);
                        bMatched = false;
                        break;
                    }
                }
            }

            if (bMatched)
            {
                UE_LOG(LogTemp, Warning, TEXT("Command Matched: %s"), *Command.name);
                StartCommand(Command.name);

                inputBuffer.RemoveAt(i, CommandLength);
                return true;
            }
        }
    }

    return false;
}

void ABaseCharacter::StartCommand(FString CommandName)
{
    for (FCommand& Command : characterCommands)
    {
        if (!CommandName.Equals(Command.name))
        {
            continue;
        }
        UE_LOG(LogTemp, Warning, TEXT("The character is using the command: %s."), *CommandName);
        Command.hasUsedCommand = true;
        PlayAnimSafe(Command.ComboAttackMontage);
    }
}

void ABaseCharacter::HandleInput(ECommandInput Input)
{
    FInputInfo info;
    info.inputName = Input;
    info.timeStamp = GetWorld()->GetTimeSeconds();
    
    bool bCommandMatched = AddInputToInputBuffer(info);
    
    if (bCommandMatched)
    {
        GetWorld()->GetTimerManager().ClearTimer(InputConfirmHandle);
        return;
    }

    StartPendingInput(Input);
}

void ABaseCharacter::StartPendingInput(ECommandInput Input)
{
    pendingInput.inputName = Input;
    pendingInput.timeStamp = GetWorld()->GetTimeSeconds();
    bIsWaitingForInput = true;

    GetWorld()->GetTimerManager().ClearTimer(InputConfirmHandle);

    GetWorld()->GetTimerManager().SetTimer(InputConfirmHandle, this,
        &ABaseCharacter::PendingInput, 0.05f, false);

}

void ABaseCharacter::PendingInput()
{
    if (!bIsWaitingForInput)
    {
        return;
    }

    bIsWaitingForInput = false;
    ExecuteActionForInput(pendingInput.inputName);
}

void ABaseCharacter::CancelPendingInput()
{
    bIsWaitingForInput = false;
    GetWorld()->GetTimerManager().ClearTimer(InputConfirmHandle);
}

void ABaseCharacter::ExecuteActionForInput(ECommandInput Input)
{
    if (Input == ECommandInput::Forward || Input == ECommandInput::Backward)
    {
        return;
    }

    if (InputMontageMap.Contains(Input))
    {
        UAnimMontage* Montage = InputMontageMap[Input];
        if (Montage && animInstance)
        {
            PlayAnimSafe(Montage);
        }
    }
}

void ABaseCharacter::PlayAnimSafe(UAnimMontage* MontageToPlay)
{
    if (!MontageToPlay || !animInstance)
    {
        return;
    }

    bool bIsException = false;

    if (DamagedMontage || DamagedMontage == MontageToPlay)
    {
        bIsException = true;
    }

    if (!bIsException && animInstance->IsAnyMontagePlaying())
    {
        return;
    }
    animInstance->Montage_Play(MontageToPlay);
}

void ABaseCharacter::MoveAction(const FInputActionValue& Value)
{
    FVector2D StickInput = Value.Get<FVector2D>();

    const float HorizontalDeadzone = 0.2f;
    const float JumpThreshold = 0.8f;

    if (FMath::Abs(StickInput.X) > HorizontalDeadzone)
    {
        AddMovementInput(GetActorForwardVector(), StickInput.X);
    }

    if (StickInput.Y >= JumpThreshold)
    {
        if (!animInstance->bIsJumping)
        {
            if (JumpMontage)
            {
                animInstance->Montage_Play(JumpMontage);
            }
        }
    }
}

void ABaseCharacter::AttackAction(const FInputActionValue& Value)
{
    if (Value.Get<bool>())
    {
        PlayAnimMontage(Combo1Montage);
    }
}

void ABaseCharacter::JumpAction(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Warning, TEXT("JUMP key was pressed!"));
    if (Value.Get<bool>()&& !animInstance->bIsJumping)
    {
        movementComponent->AirControl = 0.0f;
        movementComponent->FallingLateralFriction = 0.0f;
        movementComponent->MaxAcceleration = 5000.0f;
        movementComponent->MaxWalkSpeedCrouched = 600.0f;
        if (JumpMontage && animInstance)
        {
            animInstance->Montage_Play(JumpMontage);
        }
    }
}

void ABaseCharacter::CrouchAction(const FInputActionValue& Value)
{
    if (Value.Get<bool>())
    {
        Crouch();
    }
    else
    {
        UnCrouch();
    }
}

void ABaseCharacter::MoveStarted(const FInputActionValue& Value)
{
    float MovementValue = Value.Get<float>();
   /* if (MovementValue != 0.0f)
    {
        RequestStateChange(ECharacterState::Walking);
    }*/
}

void ABaseCharacter::MoveCompleted(const FInputActionValue& Value)
{
    float MovementValue = Value.Get<float>();

}

void ABaseCharacter::GamePadFaceButtonBottomAction(const FInputActionValue& Value)
{
    //if (Value.Get<bool>())
    //{
    //    UE_LOG(LogTemp, Warning, TEXT("GamePad A is Pressed"));
    //    FInputInfo inputinfo;
    //    inputinfo.inputName = ECommandInput::A;
    //    inputinfo.timeStamp = GetWorld()->GetTimeSeconds();
    //    AddInputToInputBuffer(inputinfo);
    //    if (animInstance && L_PunchMontage)
    //    {
    //        animInstance->Montage_Play(L_PunchMontage);
    //    }
    //}
    //else
    //{
    //    UE_LOG(LogTemp, Warning, TEXT("GamePad A is not Pressed"));
    //}
    if (Value.Get<bool>())
    {
        HandleInput(ECommandInput::A);
    }
}

void ABaseCharacter::GamePadFaceButtonRightAction(const FInputActionValue& Value)
{
    if (Value.Get<bool>())
    {
        HandleInput(ECommandInput::B);
    }
}

void ABaseCharacter::GamePadFaceButtonLeftAction(const FInputActionValue& Value)
{
    if (Value.Get<bool>())
    {
        HandleInput(ECommandInput::X);
    }
}

void ABaseCharacter::GamePadFaceButtonTopAction(const FInputActionValue& Value)
{
    if (Value.Get<bool>())
    {
        HandleInput(ECommandInput::Y);
    }
}

void ABaseCharacter::GamePadRightShoulderAction(const FInputActionValue& Value)
{
    if (Value.Get<bool>())
    {

    }
}

void ABaseCharacter::GamePadLeftShoulderAction(const FInputActionValue& Value)
{
    if (Value.Get<bool>())
    {

    }
}

void ABaseCharacter::GamePadRightTriggerAction(const FInputActionValue& Value)
{
    if (Value.Get<bool>())
    {

    }
}

void ABaseCharacter::GamePadLeftTriggerAction(const FInputActionValue& Value)
{
    if (Value.Get<bool>())
    {

    }
}

void ABaseCharacter::Landed(const FHitResult& Hit)
{
    Super::OnLanded(Hit);
    if (animInstance)
    {
        animInstance->bIsJumping = false;
        movementComponent->AirControl = 1.0f;
    }
}

void ABaseCharacter::ForwardAction(const FInputActionValue& Value)
{
    if (!Value.Get<bool>())
    {
        return;
    }

    FInputInfo inputinfo;
    inputinfo.inputName = ECommandInput::Forward;
    inputinfo.timeStamp = GetWorld()->GetTimeSeconds();
    AddInputToInputBuffer(inputinfo);
}

void ABaseCharacter::BackwardAction(const FInputActionValue& Value)
{
    if (!Value.Get<bool>())
    {
        return;
    }

    FInputInfo inputinfo;
    inputinfo.inputName = ECommandInput::Backward;
    inputinfo.timeStamp = GetWorld()->GetTimeSeconds();
    AddInputToInputBuffer(inputinfo);
}

void ABaseCharacter::LeftPunchAction(const FInputActionValue& Value)
{

}

void ABaseCharacter::RightPunchAction(const FInputActionValue& Value)
{
}

void ABaseCharacter::LeftKickAction(const FInputActionValue& Value)
{
}

void ABaseCharacter::RightKickAction(const FInputActionValue& Value)
{
}
