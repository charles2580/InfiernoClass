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
    StateManager = CreateDefaultSubobject<UStateManager>(TEXT("StateManager"));
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
            Subsystem->AddMappingContext(PlayerMappingContext, 0);
        }
    }
    StateManager->Initialize(this);
    StateManager->ChangeState(UIdleState::StaticClass());
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (CurrentState)
    {
        CurrentState->Update(this, DeltaTime);
    }
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

void ABaseCharacter::MoveForward(const FInputActionValue& Value)
{
    float MovementValue = Value.Get<float>();
    if (MovementValue != 0.0f)
    {
        AddMovementInput(GetActorForwardVector(), MovementValue);
        if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
        {
            Speed = GetVelocity().Size();
            Speed = (MovementValue < 0) ? -Speed : Speed; // 방향에 따라 속도 설정
        }
        //if (MovementValue < 0)
        //{
        //    RequestStateChange(ECharacterState::Walking);
        //}
        //else
        //{
        //    RequestStateChange(ECharacterState::Block);
        //}
    }
}

void ABaseCharacter::JumpAction(const FInputActionValue& Value)
{
    if (Value.Get<bool>())
    {
        Jump();
    }
    else
    {
        StopJumping();
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
    if (MovementValue != 0.0f)
    {
        RequestStateChange(ECharacterState::Walking);
    }
}

void ABaseCharacter::MoveCompleted(const FInputActionValue& Value)
{
    float MovementValue = Value.Get<float>();
    if (MovementValue != 0.0f) {
        RequestStateChange(ECharacterState::Idle);
    }
}

