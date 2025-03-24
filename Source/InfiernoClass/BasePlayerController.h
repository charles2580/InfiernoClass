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
		class UInputAction* IA_Move;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputAction* IA_Jump;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputAction* IA_Attack;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputAction* IA_Gamepad_FaceButton_Bottom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputAction* IA_Gamepad_FaceButton_Right;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputAction* IA_Gamepad_FaceButton_Left;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputAction* IA_Gamepad_FaceButton_Top;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputAction* IA_Gamepad_LeftShoulder;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputAction* IA_Gamepad_RightShoulder;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputAction* IA_Gamepad_LeftTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputAction* IA_Gamepad_RightTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputMappingContext* MappingContext_Player1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputMappingContext* MappingContext_Player2;

	void HandleMove(const FInputActionValue& Value);
	void HandleJump(const FInputActionValue& Value);
	void HandleAttack(const FInputActionValue& Value);
	void HandleGamePadFaceButtonBottom(const FInputActionValue& Value);
	void HandleGamePadFaceButtonRight(const FInputActionValue& Value);
	void HandleGamePadFaceButtonLeft(const FInputActionValue& Value);
	void HandleGamePadFaceButtonTop(const FInputActionValue& Value);
	void HandleGamePadLeftShoulder(const FInputActionValue& Value);
	void HandleGamePadRightShoulder(const FInputActionValue& Value);
	void HandleGamePadLeftTrigger(const FInputActionValue& Value);
	void HandleGamePadRightTrigger(const FInputActionValue& Value);
};
