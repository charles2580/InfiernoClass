// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MotionWarpingComponent.h"
#include "GameFramework/RootMotionSource.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Speed = 0;
    Block = false;
    //StateManager = CreateDefaultSubobject<UStateManager>(TEXT("StateManager"));
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

//void ABaseCharacter::RequestStateChange(ECharacterState NewState)
//{
//    switch (NewState)
//    {
//    case ECharacterState::Idle:
//        StateManager->ChangeState(UIdleState::StaticClass());
//        break;
//    case ECharacterState::Walking:
//        StateManager->ChangeState(UWalkState::StaticClass());
//        break;
//    case ECharacterState::Attack:
//        StateManager->ChangeState(UAttackState::StaticClass());
//        break;
//    case ECharacterState::Hit:
//        StateManager->ChangeState(UHitState::StaticClass());
//        break;
//    case ECharacterState::Block:
//        //StateManager->ChangeState(UHitState::StaticClass());
//        break;
//    }
//
//}

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

bool ABaseCharacter::ApplyDamage(float Damage, EAttackType AttackType, bool bCasuesAriborne)
{
    // === ��� ���� ó�� ===
    if (AttackType == EAttackType::High)
    {
        if (CurrentState == ECharacterState::Crunch)
        {
            UE_LOG(LogTemp, Log, TEXT("%s avoided high attack by crouching!"), *GetName());
            return false; // ���� ��ȿ
        }

        if (LastHorizontalInput == ECommandInput::Backward)
        {
            SetCharacterState(ECharacterState::Block);
            PlayAnimMontageSafe(HighBlockMontage, false);
            UE_LOG(LogTemp, Log, TEXT("%s blocked high attack!"), *GetName());
            return false; // ���ŷ ����
        }
    }

    // === �ߴ� ���� ó�� ===
    if (AttackType == EAttackType::Mid)
    {
        if (LastHorizontalInput == ECommandInput::Backward)
        {
            SetCharacterState(ECharacterState::Block);
            PlayAnimMontageSafe(MidBlockMontage, false);
            UE_LOG(LogTemp, Log, TEXT("%s blocked mid attack!"), *GetName());
            return false; // ���ŷ ����
        }
    }

    // === �ϴ� ���� ó�� ===
    if (AttackType == EAttackType::Low)
    {
        if (CurrentState == ECharacterState::Jump)
        {
            UE_LOG(LogTemp, Log, TEXT("%s avoided low attack by jumping!"), *GetName());
            return false; // ������ ȸ�� ����
        }
        if (CurrentState == ECharacterState::Crunch)
        {
            SetCharacterState(ECharacterState::Block);
            PlayAnimMontageSafe(LowBlockMontage, true);
            return false;
        }
    }

    if (HitEffect)
    {
        FName SpawnSocketName;

        switch (AttackType)
        {
        case EAttackType::High:
            SpawnSocketName = HitEffectSocket_High;
            break;
        case EAttackType::Mid:
            SpawnSocketName = HitEffectSocket_Mid;
            break;
        case EAttackType::Low:
            SpawnSocketName = HitEffectSocket_Low;
            break;
        default:
            SpawnSocketName = NAME_None;
            break;
        }

        if (SpawnSocketName != NAME_None)
        {
            UNiagaraSystem* NiagaraEffect = HitEffect;
            if (NiagaraEffect)
            {
                FVector SpawnLoc = GetMesh()->GetSocketLocation(SpawnSocketName);
                UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraEffect, SpawnLoc);
            }
        }

        if (CurrentState == ECharacterState::Airbone)
        {
            if (airbornegauge > 0)
            {
                LaunchCharacterAirborne(100.0f, 100.0f, 0.7f, true);
                airbornegauge -= 50.0f;
                UE_LOG(LogTemp, Warning, TEXT("Launch: Set to Airbone, current = %d"), (int32)CurrentState);
                PlayAnimMontageSafe(AirborneDamagedMontage, false);
            }
            return true;
        }

        if (bCasuesAriborne && CurrentState !=ECharacterState::Airbone)
        {
            LaunchCharacterAirborne(100.0f, 250.0f, 0.9f, false);
            PlayAnimMontageSafe(AirborneDamagedMontage, false);
            return true;
        }
        
    }
    return true;
}

ECharacterState ABaseCharacter::GetCharacterState() const
{
    return CurrentState;
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
    const float MaxInputDelay = 0.3f;

    for (const auto& Command : characterCommands)
    {
        const int32 CommandLength = Command.inputs.Num();
        const int32 BufferLength = inputBuffer.Num();

        if (BufferLength < CommandLength)
        {
            continue;
        }

        // inputBuffer ��ü�� �����̵� ������ ������� ��ȸ
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

                // �ð� ���� �˻� (j > 0 ����)
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
    
    InputQueue.Add(info);
    UE_LOG(LogTemp, Log, TEXT("input : %s"), *UEnum::GetValueAsString(Input));

    if (bCommandMatched)
    {
        GetWorld()->GetTimerManager().ClearTimer(InputConfirmHandle);
        InputQueue.Empty();
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
    if (Input == ECommandInput::Forward || Input == ECommandInput::Backward || Input == ECommandInput::Jump ||Input == ECommandInput::Crunch)
    {
        return;
    }

    if (CurrentState == ECharacterState::Crunch)
    {
        if (CrouchMontageMap.Contains(Input))
        {
            UAnimMontage* Montage = CrouchMontageMap[Input];
            if (Montage && animInstance)
            {
                PlayAnimMontageSafe(Montage, true);
                SetCharacterState(ECharacterState::Attack);
                return;
            }
        }
    }

    else
    {    
        if (InputMontageMap.Contains(Input))
        {
            UAnimMontage* Montage = InputMontageMap[Input];
            if (Montage && animInstance)
            {
                PlayAnimMontageSafe(Montage, false);
                SetCharacterState(ECharacterState::Attack);
            }
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

void ABaseCharacter::PlayRootMotionJump()
{
    if (!GetCharacterMovement()) 
    {
        return;
    }
    TSharedPtr<FRootMotionSource_JumpForce> JumpForce = MakeShared<FRootMotionSource_JumpForce>();
    JumpForce->InstanceName = FName("RootMotion_JumpForce");
    JumpForce->AccumulateMode = ERootMotionAccumulateMode::Override;
    JumpForce->Priority = 10;
    JumpForce->Duration = 0.7f;
    JumpForce->Distance = 0.0f;
    JumpForce->Height = 100.0f;
    JumpForce->PathOffsetCurve = JumpCurve;
    JumpForce->bDisableTimeout = false; 
    
    GetCharacterMovement()->ApplyRootMotionSource(JumpForce);
    
}

void ABaseCharacter::LaunchCharacterAirborne(float Distance, float Height, float Duration, bool bIsChainHit)
{
    if (CurrentState != ECharacterState::Airbone)
    {
        SetCharacterState(ECharacterState::Airbone);
    }
    GetCharacterMovement()->RemoveRootMotionSource(FName("RootMotion_AirborneForce"));
    PlayRootMotionAirborne(Distance, Height, Duration, bIsChainHit);
}

void ABaseCharacter::PlayRootMotionAirborne(float Distance, float Height, float Duration, bool bIsChainHit)
{
    if (!GetCharacterMovement())
    {
        return;
    }

    UCurveVector* SelectedCurve = bIsChainHit ? ChainAirborneCurve : InitialAirborneCurve;

    float direction = (GetActorForwardVector().X > 0) ? -1.0f : 1.0f;

    TSharedPtr<FRootMotionSource_JumpForce> AirborneForce = MakeShared<FRootMotionSource_JumpForce>();
    AirborneForce->InstanceName = FName("RootMotion_AirborneForce");
    AirborneForce->AccumulateMode = ERootMotionAccumulateMode::Override;
    AirborneForce->Priority = 10;
    AirborneForce->Duration = Duration;
    AirborneForce->Distance = Distance * direction;
    AirborneForce->Height = Height;
    AirborneForce->PathOffsetCurve = SelectedCurve;
    AirborneForce->bDisableTimeout = false;

    GetCharacterMovement()->ApplyRootMotionSource(AirborneForce);
}

void ABaseCharacter::SetCharacterState(ECharacterState NewState)
{
    if (CurrentState == NewState)
        return;

    CurrentState = NewState;

    UE_LOG(LogTemp, Log, TEXT("change sate to %s"), *UEnum::GetValueAsString(NewState));
}

void ABaseCharacter::MoveAction(const FInputActionValue& Value)
{
    //FVector2D StickInput = Value.Get<FVector2D>();
    //const float HorizontalDeadzone = 0.2f;

    //if (CurrentState == ECharacterState::Attack ||
    //    CurrentState == ECharacterState::Jump ||
    //    CurrentState == ECharacterState::Crunch)
    //{
    //    return;
    //}

    //// �¿� �̵�
    //if (FMath::Abs(StickInput.X) > HorizontalDeadzone)
    //{
    //    AddMovementInput(GetActorForwardVector(), StickInput.X);
    //    if (CurrentState != ECharacterState::Walking)
    //    {
    //        CurrentState = ECharacterState::Walking;
    //    }
    //}

    //else if (FMath::Abs(StickInput.X) < HorizontalDeadzone)
    //{
    //    if (CurrentState != ECharacterState::Idle && CurrentState != ECharacterState::Jump
    //        && CurrentState != ECharacterState::Attack)
    //    {
    //        CurrentState = ECharacterState::Idle;
    //    }
    //}
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
    const FVector2D StickInput = Value.Get<FVector2D>();
    const float Deadzone = 0.2f;
    const float JumpThreshold = 0.7f;
    const float CrouchThreshold = -0.5f;

    const FVector ForwardDir = GetActorForwardVector();
    const float ForwardX = ForwardDir.X;

    // === 1. �¿� �Է� ó�� ===
    float AdjustedX = StickInput.X * FMath::Sign(ForwardX);  // ���� ���� ���

    if (FMath::Abs(AdjustedX) > Deadzone)
    {
        ECommandInput DirInput = (AdjustedX > 0) ? ECommandInput::Forward : ECommandInput::Backward;

        animInstance->directionX = (AdjustedX > 0) ? 1.0f : -1.0f;

        if (LastHorizontalInput != DirInput)
        {
            HandleInput(DirInput);
            LastHorizontalInput = DirInput;
        }

        if (CurrentState != ECharacterState::Crunch &&
            CurrentState != ECharacterState::Jump)
        {
            AddMovementInput(ForwardDir, AdjustedX);
            if (CurrentState == ECharacterState::Idle)
            {
                SetCharacterState(ECharacterState::Walking);
            }
        }
    }
    else
    {
        LastHorizontalInput = ECommandInput::None;
        if (CurrentState == ECharacterState::Walking)
        {
            SetCharacterState(ECharacterState::Idle);
        }
    }

    // === 2. �� ���� �Է� (����) ===
    if (StickInput.Y >= JumpThreshold && LastVerticalInput != ECommandInput::Jump)
    {
        HandleInput(ECommandInput::Jump);
        LastVerticalInput = ECommandInput::Jump;

        if (CurrentState != ECharacterState::Attack &&
            CurrentState != ECharacterState::Jump &&
            animInstance && !animInstance->bIsJumping)
        {
            PlayRootMotionJump();
            SetCharacterState(ECharacterState::Jump);
        }
    }

    // === 3. �Ʒ� ���� �Է� (ũ��ġ) ===
    else if (StickInput.Y <= CrouchThreshold && LastVerticalInput != ECommandInput::Crunch)
    {
        HandleInput(ECommandInput::Crunch);
        LastVerticalInput = ECommandInput::Crunch;

        if (CurrentState != ECharacterState::Crunch)
        {
            SetCharacterState(ECharacterState::Crunch);
        }
    }

    // === 4. �߸����� ���ƿ��� �� �ʱ�ȭ ===
    else if (FMath::Abs(StickInput.Y) < Deadzone)
    {
        LastVerticalInput = ECommandInput::None;

        if (CurrentState != ECharacterState::Idle &&
            CurrentState != ECharacterState::Attack &&
            CurrentState != ECharacterState::Jump &&
            CurrentState != ECharacterState::Walking &&
            CurrentState != ECharacterState::Airbone)
        {
            SetCharacterState(ECharacterState::Idle);
        }
    }
}

void ABaseCharacter::CrunchAction(const FInputActionValue& Value)
{
    //FVector2D StickInput = Value.Get<FVector2D>();
    //const float JumpThreshold = 0.7f;
    //const float VerticalDeadzone = 0.2f;
    //const float DownThreshold = -0.5f;

    //if (StickInput.Y >= JumpThreshold)
    //{
    //    HandleInput(ECommandInput::Jump);
    //    if (CurrentState == ECharacterState::Attack)
    //    {
    //        return;
    //    }

    //    if (CurrentState != ECharacterState::Jump && !animInstance->bIsJumping)
    //    {
    //        PlayRootMotionJump();
    //    }
    //}

    //// �Ʒ� ���� �Է�: ���׸��� ����
    //if (StickInput.Y < DownThreshold)
    //{
    //    if (CurrentState != ECharacterState::Crunch)
    //    {
    //        HandleInput(ECommandInput::Crunch);
    //        CurrentState = ECharacterState::Crunch;
    //    }
    //}

    //else if (FMath::Abs(StickInput.Y) < VerticalDeadzone)
    //{
    //    if (CurrentState != ECharacterState::Idle && CurrentState != ECharacterState::Jump
    //        && CurrentState != ECharacterState::Attack && CurrentState != ECharacterState::Walking)
    //    {
    //        CurrentState = ECharacterState::Idle;
    //    }
    //}
}

void ABaseCharacter::CrunchReleased(const FInputActionValue& Value)
{
    if (!Value.Get<bool>())
    {
        return;
    }
    if (CurrentState == ECharacterState::Crunch)
    {
        CurrentState = ECharacterState::Idle;
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
    if (CurrentState == ECharacterState::Jump)
    {
        SetCharacterState(ECharacterState::Idle);
        if (animInstance)
        {
            animInstance->bIsJumping = false;
        }
        GetCharacterMovement()->RemoveRootMotionSource(FName("RootMotion_JumpForce"));
    }

    if (CurrentState == ECharacterState::Airbone)
    {
        SetCharacterState(ECharacterState::NockDown);
        airbornegauge = 100.0f;
        GetCharacterMovement()->RemoveRootMotionSource(FName("RootMotion_AirborneForce"));
    }

    Super::Landed(Hit);
    UE_LOG(LogTemp, Warning, TEXT("is landed"));
}

void ABaseCharacter::ForwardAction(const FInputActionValue& Value)
{
    //FVector Stick = Value.Get<FVector>();
    //const float Deadzone = 0.2f;

    //if (CurrentState == ECharacterState::Attack ||
    //    CurrentState == ECharacterState::Jump ||
    //    CurrentState == ECharacterState::Crunch)
    //{
    //    return;
    //}

    //// ��ƽ �߸�: IDLE ���·� ��ȯ
    //if (FMath::Abs(Stick.X) < Deadzone)
    //{
    //    // ��, ����/���� �� �߿��� ���� ����
    //    if (CurrentState != ECharacterState::Attack &&
    //        CurrentState != ECharacterState::Jump &&
    //        CurrentState != ECharacterState::Crunch)
    //    {
    //        SetCharacterState(ECharacterState::Idle);
    //    }

    //    // ���� �Է� �ʱ�ȭ
    //    LastDirectionalInput = ECommandInput::None;
    //    return;
    //}

    //// ��ƽ �Է� ����: �̵� ó��
    //float FacingX = GetActorForwardVector().X;
    //float AdjustedInputX = Stick.X * FacingX;

    //FVector MoveDir = GetActorForwardVector() * FMath::Sign(AdjustedInputX);
    //AddMovementInput(MoveDir, 1.0f);

    //// ���� ����: �̵� ���̶�� Walking
    //if (CurrentState == ECharacterState::Idle)
    //{
    //    SetCharacterState(ECharacterState::Walking);
    //}

    //// ���� �Է� ���� ó��
    //ECommandInput CurrentInput = (AdjustedInputX > 0) ? ECommandInput::Forward : ECommandInput::Backward;
    //if (CurrentInput != LastDirectionalInput)
    //{
    //    HandleInput(CurrentInput);
    //    LastDirectionalInput = CurrentInput;
    //}
}

void ABaseCharacter::BackwardAction(const FInputActionValue& Value)
{
    FVector Stick = Value.Get<FVector>();
    const float Deadzone = 0.2f;
}

void ABaseCharacter::LeftPunchAction(const FInputActionValue& Value)
{
    if (!Value.Get<bool>())
    {
        return;
    }

    if (CurrentState != ECharacterState::Idle &&
        CurrentState != ECharacterState::Crunch)
    {
        return;
    }

    HandleInput(ECommandInput::A);
}

void ABaseCharacter::RightPunchAction(const FInputActionValue& Value)
{
    if (!Value.Get<bool>())
    {
        return;
    }

    if (CurrentState != ECharacterState::Idle &&
        CurrentState != ECharacterState::Crunch)
    {
        return;
    }

    HandleInput(ECommandInput::B);
}

void ABaseCharacter::LeftKickAction(const FInputActionValue& Value)
{
    if (!Value.Get<bool>())
    {
        return;
    }

    if (CurrentState != ECharacterState::Idle &&
        CurrentState != ECharacterState::Crunch)
    {
        return;
    }

    HandleInput(ECommandInput::X);

}

void ABaseCharacter::RightKickAction(const FInputActionValue& Value)
{
    if (!Value.Get<bool>())
    {
        return;
    }

    if (CurrentState != ECharacterState::Idle &&
        CurrentState != ECharacterState::Crunch)
    {
        return;
    }

    HandleInput(ECommandInput::Y);
}
