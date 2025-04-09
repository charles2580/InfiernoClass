// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NS_MoveToDirection.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ERootMotionDirection : uint8
{
	FORWARD UMETA(DisplayName = "Forward"),
	BACKWARD UMETA(DisplayName = "Backward")
};


UCLASS()
class INFIERNOCLASS_API UNS_MoveToDirection : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	// 이동 속도 (cm/s)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RootMotion")
		float MoveSpeed = 600.f;

	// 이동 방향
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RootMotion")
		ERootMotionDirection Direction = ERootMotionDirection::FORWARD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RootMotion")
		FName InstanceName = FName("RootMotionMove");

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	virtual FString GetNotifyName_Implementation() const override
	{
		return TEXT("MoveToDirection");
	}
};
