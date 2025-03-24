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

USTRUCT(BlueprintType)
struct FInputInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FString inputName;

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
	TArray<FString> inputs;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UHitboxComponent* HitboxComponent;

protected:

	UFUNCTION(BlueprintCallable)
	void AddInputToInputBuffer(FInputInfo _inputinfo);

	UFUNCTION(BlueprintCallable)
	void RemoveInputFromInputBuffer();

	UFUNCTION(BlueprintCallable)
	void CheckInputBufferForCommand();
	
	UFUNCTION(BlueprintCallable)
	void StartCommand(FString _commandName);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TArray<FInputInfo> inputBuffer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TArray<FCommand> characterCommands;

	FTimerHandle inputBufferTimerHandle;
	float removeInputFromBufferTime;

private:
	UCharacterMovementComponent* movementComponent;
	UPlayerAnimInstance* animInstance;
};
