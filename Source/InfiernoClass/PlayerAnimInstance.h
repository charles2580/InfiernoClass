// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/Character.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class INFIERNOCLASS_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool bIsAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool bIsJumping;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool bIsBlocking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	float Speed;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	APawn* Pawn;
};
