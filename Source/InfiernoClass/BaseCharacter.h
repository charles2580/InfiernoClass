// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "StateManager.h"
#include "BaseState.h"
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
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_MoveForward;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Jump;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Crouch;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void RequestStateChange(ECharacterState NewState);

	UFUNCTION(BlueprintCallable, Category = "Animation")
	float GetSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "Animation")
	bool GetBlock() const;

	TScriptInterface<IBaseState> CurrentState;

	UPROPERTY()
	UStateManager* StateManager;

	UPROPERTY(EditAnywhere, Category = "Animation");
	float Speed;

	UPROPERTY(EditAnywhere, Category = "Animation");
	bool Block;
protected:

	void MoveForward(const FInputActionValue& Value);
	void JumpAction(const FInputActionValue& Value);
	void CrouchAction(const FInputActionValue& Value);
	void MoveStarted(const FInputActionValue& Value);
	void MoveCompleted(const FInputActionValue& Value);
};
