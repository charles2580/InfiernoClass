// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerAnimInstance.h"
#include "StateManager.h"
#include "BaseState.h"
#include "HitboxComponent.h"
#include "GameFramework/RootMotionSource.h"
#include "BaseCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Idle,
	Walking,
	Attack,
	Hit,
	Block
};

UENUM(BlueprintType)
enum class ECommandInput : uint8
{
	Forward UMETA(DisplayName = "Forward"),
	Backward UMETA(DisplayName = "Backward"),
	Jump UMETA(DisplayName = "Jump"),
	Crunch UMETA(DisplayName = "Crunch"),
	A UMETA(DisplayName = "A"),
	B UMETA(DisplayName = "B"),
	X UMETA(DisplayName = "X"),
	Y UMETA(DisplayName = "Y")
};

USTRUCT(BlueprintType)
struct FInputInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	ECommandInput inputName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float timeStamp;
};

USTRUCT(BlueprintType)
struct FCommand
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TArray<ECommandInput> inputs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool hasUsedCommand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UAnimMontage* ComboAttackMontage;
};

UCLASS()
class INFIERNOCLASS_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_MoveForward;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Jump;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Crouch;

	UPROPERTY(EditAnywhere, Category = "Animaiton")
	UAnimMontage* DamagedMontage;

	UPROPERTY(EditAnywhere, Category = "Animaiton")
	UAnimMontage* JumpMontage;

	UPROPERTY(EditAnywhere, Category = "Animaiton")
	UAnimMontage* L_PunchMontage;

	UPROPERTY(EditAnywhere, Category = "Animaiton")
	UAnimMontage* Combo1Montage;

	UPROPERTY(EditAnywhere, Category = "Animaiton")
	UAnimMontage* Combo2Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Warping")
	class UMotionWarpingComponent* MotionWarpingComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void RequestStateChange(ECharacterState NewState);
	virtual void Landed(const FHitResult& Hit) override;

	void ForwardAction(const FInputActionValue& Value);
	void BackwardAction(const FInputActionValue& Value);
	void LeftPunchAction(const FInputActionValue& Value);
	void RightPunchAction(const FInputActionValue& Value);
	void LeftKickAction(const FInputActionValue& Value);
	void RightKickAction(const FInputActionValue& Value);

	void MoveAction(const FInputActionValue& Value);
	void AttackAction(const FInputActionValue& Value);
	void JumpAction(const FInputActionValue& Value);
	void CrouchAction(const FInputActionValue& Value);
	void MoveStarted(const FInputActionValue& Value);
	void MoveCompleted(const FInputActionValue& Value);
	void GamePadFaceButtonBottomAction(const FInputActionValue& Value);
	void GamePadFaceButtonRightAction(const FInputActionValue& Value);
	void GamePadFaceButtonLeftAction(const FInputActionValue& Value);
	void GamePadFaceButtonTopAction(const FInputActionValue& Value);
	void GamePadRightShoulderAction(const FInputActionValue& Value);
	void GamePadLeftShoulderAction(const FInputActionValue& Value);
	void GamePadRightTriggerAction(const FInputActionValue& Value);
	void GamePadLeftTriggerAction(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void RemoveInputFromInputBuffer();

	UFUNCTION(BlueprintCallable, Category = "Animation")
	float GetSpeed() const;
	UFUNCTION(BlueprintCallable, Category = "Animation")
	bool GetBlock() const;

	void SetWarpTarget(FName TargetName, const FTransform& TargetTransform);
	void ClearWarpTarget(FName TargetName);

	void ApplyDamage(float Damage);

	TScriptInterface<IBaseState> CurrentState;

	UPROPERTY()
	UStateManager* StateManager;

	UPROPERTY(EditAnywhere, Category = "Animation")
	float Speed;
	UPROPERTY(EditAnywhere, Category = "Animation")
	bool Block;

protected:

	UFUNCTION(BlueprintCallable)
	bool AddInputToInputBuffer(FInputInfo _inputinfo);

	UFUNCTION(BlueprintCallable)
	bool CheckInputBufferForCommand();
	
	UFUNCTION(BlueprintCallable)
	void StartCommand(FString CommandName);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TArray<FInputInfo> inputBuffer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TArray<FCommand> characterCommands;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TMap<ECommandInput, UAnimMontage*> InputMontageMap;

	FTimerHandle inputBufferTimerHandle;
	float removeInputFromBufferTime;

private:
	UCharacterMovementComponent* movementComponent;
	UPlayerAnimInstance* animInstance;

	TArray<FInputInfo> InputQueue;

	bool bIsWaitingForInput = false;
	bool bIsPlayingMontage = false;
	FInputInfo pendingInput;
	FTimerHandle InputConfirmHandle;

	void HandleInput(ECommandInput Input);
	void StartPendingInput(ECommandInput Input);
	void PendingInput();
	void CancelPendingInput();
	void ExecuteActionForInput(ECommandInput Input);

	void PlayAnimSafe(UAnimMontage* MontageToPlay);
};
