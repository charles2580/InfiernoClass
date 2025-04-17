// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class INFIERNOCLASS_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputAction* IA_AnyKey;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputAction* IA_Move;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputAction* IA_Jump;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputAction* IA_Attack;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputAction* IA_Forward;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputAction* IA_Backward;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputAction* IA_Crunch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputAction* IA_CrunchReleased;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputAction* IA_LeftPunch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputAction* IA_RightPunch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputAction* IA_LeftKick;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputAction* IA_RightKick;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputMappingContext* MappingContext_Player1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputMappingContext* MappingContext_Player2;

	void HandleMoveInput(const FInputActionValue& Value);
	void HandleJumpInput(const FInputActionValue& Value);
	void HandleAttackInput(const FInputActionValue& Value);
	void HandleForwardInput(const FInputActionValue& Value);
	void HandleBackwardInput(const FInputActionValue& Value);
	void HandleCrunchInput(const FInputActionValue& Value);
	void HandleCrunchReleasedInput(const FInputActionValue& Value);
	void HandleLeftPunchInput(const FInputActionValue& Value);
	void HandleRightPunchInput(const FInputActionValue& Value);

	void HandleLeftKickInput(const FInputActionValue& Value);
	void HandleRightKickInput(const FInputActionValue& Value);

	void HandleRemoveInputFromInputBuffer(const FInputActionValue& Value);
};
