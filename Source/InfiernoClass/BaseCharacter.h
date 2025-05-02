// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerAnimInstance.h"
#include "HitboxComponent.h"
#include "GameFramework/RootMotionSource.h"
#include "NiagaraSystem.h"             
#include "NiagaraFunctionLibrary.h"  
#include "BaseCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Idle,
	Walking,
	Attack,
	Jump,
	Airbone,
	Damaged,
	NockDown,
	Crunch,
	Hit,
	Block
};

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	High,
	Mid,
	Low
};

UENUM(BlueprintType)
enum class ECommandInput : uint8
{
	None UMETA(DisplayName = "None"),
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
		UAnimMontage* HighBlockMontage;

	UPROPERTY(EditAnywhere, Category = "Animaiton")
		UAnimMontage* MidBlockMontage;

	UPROPERTY(EditAnywhere, Category = "Animaiton")
		UAnimMontage* LowBlockMontage;

	UPROPERTY(EditAnywhere, Category = "Animaiton")
		UAnimMontage* AirborneDamagedMontage;

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

	//void RequestStateChange(ECharacterState NewState);
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
	void CrunchAction(const FInputActionValue& Value);
	void CrunchReleased(const FInputActionValue& Value);
	void MoveStarted(const FInputActionValue& Value);
	void MoveCompleted(const FInputActionValue& Value);


	UFUNCTION(BlueprintCallable)
		void RemoveInputFromInputBuffer();

	UFUNCTION(BlueprintCallable, Category = "Animation")
		float GetSpeed() const;
	UFUNCTION(BlueprintCallable, Category = "Animation")
		bool GetBlock() const;

	void SetWarpTarget(FName TargetName, const FTransform& TargetTransform);
	void ClearWarpTarget(FName TargetName);

	bool ApplyDamage(float Damage, EAttackType AttackType, bool bCasuesAirborne);

	//TScriptInterface<IBaseState> CurrentState;

	/*UPROPERTY()
	UStateManager* StateManager;*/

	UPROPERTY(EditAnywhere, Category = "Animation")
		float Speed;
	UPROPERTY(EditAnywhere, Category = "Animation")
		bool Block;

	UPROPERTY(BluePrintReadWrite, Category = "CharacterState")
		ECharacterState CurrentState = ECharacterState::Idle;

	UFUNCTION(BlueprintCallable, Category = "CharacterState")
		ECharacterState GetCharacterState() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterState")
		void PlayAnimMontageSafe(UAnimMontage* AnimMontage, bool bIsCrouchAttack);

	UPROPERTY(EditDefaultsOnly, Category = "Curve")
		UCurveVector* InitialAirborneCurve;

	UPROPERTY(EditDefaultsOnly, Category = "Curve")
		UCurveVector* ChainAirborneCurve;

	UPROPERTY(EditDefaultsOnly, Category = "Curve")
		UCurveVector* JumpCurve;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		TMap<ECommandInput, UAnimMontage*> CrouchMontageMap;

	FTimerHandle inputBufferTimerHandle;
	float removeInputFromBufferTime;

	// 공격당했을 때 사용할 이펙트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitEffect")
		UNiagaraSystem* HitEffect;

	// 공격당했을 때 사용할 소켓 이름들
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitEffect")
		FName HitEffectSocket_High = "HeadSocket";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitEffect")
		FName HitEffectSocket_Mid = "SpineSocket";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitEffect")
		FName HitEffectSocket_Low = "PelvisSocket";

private:

	ECommandInput LastHorizontalInput = ECommandInput::None;
	ECommandInput LastVerticalInput = ECommandInput::None;

	UCharacterMovementComponent* movementComponent;
	UPlayerAnimInstance* animInstance;

	TArray<FInputInfo> InputQueue;

	bool bIsWaitingForInput = false;
	bool bIsPlayingMontage = false;
	float airbornegauge = 100.0f;
	//float maxAirbornegauge = 100.0f;

	FInputInfo pendingInput;
	FTimerHandle InputConfirmHandle;

	void HandleInput(ECommandInput Input);
	void StartPendingInput(ECommandInput Input);
	void PendingInput();
	void CancelPendingInput();
	void ExecuteActionForInput(ECommandInput Input);

	void PlayAnimSafe(UAnimMontage* MontageToPlay);
	void PlayRootMotionJump();

	void LaunchCharacterAirborne(float Distance, float Height, float Duration, bool bIsChainHit);
	void PlayRootMotionAirborne(float Distance, float Height, float Duration, bool bIsChainHit);

	void SetCharacterState(ECharacterState NewState);

};