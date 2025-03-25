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

    //HitboxComponent = CreateDefaultSubobject<UHitboxComponent>(TEXT("HitboxComponent"));
    //HitboxComponent->SetupAttachment(GetMesh());

    removeInputFromBufferTime = 1.0f;
    characterCommands.SetNum(2);

    characterCommands[0].name = "Command #1";
    characterCommands[0].inputs.Add("A");
    characterCommands[0].inputs.Add("B");
    characterCommands[0].inputs.Add("X");
    characterCommands[0].hasUsedCommand = false;
    characterCommands[0].ComboAttackMontage = Combo1Montage;

    characterCommands[1].name = "Command #2";
    characterCommands[1].inputs.Add("A");
    characterCommands[1].inputs.Add("B");
    characterCommands[1].inputs.Add("Y");
    characterCommands[1].hasUsedCommand = false;
    characterCommands[1].ComboAttackMontage = Combo2Montage;
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

void ABaseCharacter::AddInputToInputBuffer(FInputInfo _inputinfo)
{
    inputBuffer.Add(_inputinfo);
    CheckInputBufferForCommand();
}

void ABaseCharacter::RemoveInputFromInputBuffer()
{
}

void ABaseCharacter::CheckInputBufferForCommand()
{
    int correctSequenceCounter = 0;

    for (auto currentCommand : characterCommands)
    {
        for (int commandInput = 0; commandInput < currentCommand.inputs.Num(); ++commandInput)
        {
            for (int input = 0; input < inputBuffer.Num(); ++input)
            {
                if (input + correctSequenceCounter < inputBuffer.Num())
                {
                    if (inputBuffer[input + correctSequenceCounter].inputName.Compare(currentCommand.inputs[commandInput]) == 0)
                    {
                        //UE_LOG(LogTemp, Warning, TEXT("The player added another input to the command sequence"));
                        ++correctSequenceCounter;

                        if (correctSequenceCounter == currentCommand.inputs.Num())
                        {
                            StartCommand(currentCommand.name);
                        }

                        break;
                    }
                    else
                    {
                        //UE_LOG(LogTemp, Warning, TEXT("The player borke the command sequence."));
                        correctSequenceCounter = 0;
                    }
                }
                else
                {
                    //UE_LOG(LogTemp, Warning, TEXT("The player is not yet finished with the command sequence."));
                    correctSequenceCounter = 0;
                }
            }
        }
    }
}

void ABaseCharacter::StartCommand(FString _commandName)
{
    for (int currentCommand = 0; currentCommand < characterCommands.Num(); ++currentCommand)
    {
        if (_commandName.Compare(characterCommands[currentCommand].name) == 0)
        {
            UE_LOG(LogTemp, Warning, TEXT("The character is using the command: %s."), *_commandName);
            characterCommands[currentCommand].hasUsedCommand = true;
            PlayAnimMontage(characterCommands[currentCommand].ComboAttackMontage);
        }
    }
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
    if (Value.Get<bool>())
    {
        UE_LOG(LogTemp, Warning, TEXT("GamePad A is Pressed"));
        FInputInfo inputinfo;
        inputinfo.inputName = "A";
        inputinfo.timeStamp = GetWorld()->GetTimeSeconds();
        AddInputToInputBuffer(inputinfo);
        if (animInstance && L_PunchMontage)
        {
            animInstance->Montage_Play(L_PunchMontage);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("GamePad A is not Pressed"));
    }
}

void ABaseCharacter::GamePadFaceButtonRightAction(const FInputActionValue& Value)
{
    if (Value.Get<bool>())
    {
        FInputInfo inputinfo;
        inputinfo.inputName = "B";
        inputinfo.timeStamp = GetWorld()->GetTimeSeconds();
        AddInputToInputBuffer(inputinfo);
    }
}

void ABaseCharacter::GamePadFaceButtonLeftAction(const FInputActionValue& Value)
{
    if (Value.Get<bool>())
    {
        FInputInfo inputinfo;
        inputinfo.inputName = "X";
        inputinfo.timeStamp = GetWorld()->GetTimeSeconds();
        AddInputToInputBuffer(inputinfo);
    }
}

void ABaseCharacter::GamePadFaceButtonTopAction(const FInputActionValue& Value)
{
    if (Value.Get<bool>())
    {
        FInputInfo inputinfo;
        inputinfo.inputName = "Y";
        inputinfo.timeStamp = GetWorld()->GetTimeSeconds();
        AddInputToInputBuffer(inputinfo);
    }
}

void ABaseCharacter::GamePadRightShoulderAction(const FInputActionValue& Value)
{
    if (Value.Get<bool>())
    {
        FInputInfo inputinfo;
        inputinfo.inputName = "RB";
        inputinfo.timeStamp = GetWorld()->GetTimeSeconds();
        AddInputToInputBuffer(inputinfo);
    }
}

void ABaseCharacter::GamePadLeftShoulderAction(const FInputActionValue& Value)
{
    if (Value.Get<bool>())
    {
        FInputInfo inputinfo;
        inputinfo.inputName = "LB";
        inputinfo.timeStamp = GetWorld()->GetTimeSeconds();
        AddInputToInputBuffer(inputinfo);
    }
}

void ABaseCharacter::GamePadRightTriggerAction(const FInputActionValue& Value)
{
    if (Value.Get<bool>())
    {
        FInputInfo inputinfo;
        inputinfo.inputName = "RT";
        inputinfo.timeStamp = GetWorld()->GetTimeSeconds();
        AddInputToInputBuffer(inputinfo);
    }
}

void ABaseCharacter::GamePadLeftTriggerAction(const FInputActionValue& Value)
{
    if (Value.Get<bool>())
    {
        FInputInfo inputinfo;
        inputinfo.inputName = "LT";
        inputinfo.timeStamp = GetWorld()->GetTimeSeconds();
        AddInputToInputBuffer(inputinfo);
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
