// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(IA_MoveForward, ETriggerEvent::Triggered, this, &ABaseCharacter::MoveForward);
        EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ABaseCharacter::JumpAction);
        EnhancedInputComponent->BindAction(IA_Crouch, ETriggerEvent::Triggered, this, &ABaseCharacter::CrouchAction);
    }

}

void ABaseCharacter::MoveForward(const FInputActionValue& Value)
{
    float MovementValue = Value.Get<float>();
    if (MovementValue != 0.0f)
    {
        AddMovementInput(GetActorForwardVector(), MovementValue);
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

