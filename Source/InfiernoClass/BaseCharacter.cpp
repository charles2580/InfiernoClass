// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "IdleState.h"
#include "WalkState.h"
#include "AttackState.h"
#include "HitState.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Speed = 0;
    Block = false;
    StateManager = CreateDefaultSubobject<UStateManager>(TEXT("StateManager"));
    movementComponent = GetCharacterMovement();
    removeInputFromBufferTime = 1.0f;
    characterCommands.SetNum(2);

    characterCommands[0].name = "Command #1";
    characterCommands[0].inputs.Add("A");
    characterCommands[0].inputs.Add("B");
    characterCommands[0].inputs.Add("C");
    characterCommands[0].hasUsedCommand = false;

    characterCommands[1].name = "Command #2";
    characterCommands[1].inputs.Add("A");
    characterCommands[1].inputs.Add("B");
    characterCommands[1].inputs.Add("D");
    characterCommands[1].hasUsedCommand = false;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
        if (Subsystem)
        {
            Subsystem->AddMappingContext(PlayerMappingContext, 1);
        }
    }
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
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(IA_MoveForward, ETriggerEvent::Started, this, &ABaseCharacter::MoveStarted);
        EnhancedInputComponent->BindAction(IA_MoveForward, ETriggerEvent::Completed, this, &ABaseCharacter::MoveCompleted);
        EnhancedInputComponent->BindAction(IA_MoveForward, ETriggerEvent::Triggered, this, &ABaseCharacter::MoveForward);
        EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ABaseCharacter::JumpAction);
        EnhancedInputComponent->BindAction(IA_Crouch, ETriggerEvent::Triggered, this, &ABaseCharacter::CrouchAction);
     
    }

}

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
        }
    }
}

void ABaseCharacter::MoveForward(const FInputActionValue& Value)
{
    if (movementComponent->IsFalling())
    {
        return;
    }

    float MovementValue = Value.Get<float>();
    if (MovementValue != 0.0f)
    {
        AddMovementInput(FVector(1.0f, 0.0f, 0.0f), MovementValue);
        if (animInstance)
        {
            animInstance->Speed = (MovementValue < 0) ? -animInstance->Speed : animInstance->Speed; // 방향에 따라 속도 설정
        }
        //else
        //{
        //    RequestStateChange(ECharacterState::Block);
        //}
    }
    if (MovementValue < 0)
    {
        animInstance->bIsBlocking = true;
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

void ABaseCharacter::Landed(const FHitResult& Hit)
{
    Super::OnLanded(Hit);
    if (animInstance)
    {
        animInstance->bIsJumping = false;
        movementComponent->AirControl = 1.0f;
    }
}
