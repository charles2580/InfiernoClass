// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_SetWarpTarget.generated.h"

/**
 * 
 */
UCLASS()
class INFIERNOCLASS_API UAN_SetWarpTarget : public UAnimNotify
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Warping")
		FName WarpTargetName = FName("DefaultWarpTarget");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Warping")
		FVector TargetLocation = FVector::ZeroVector;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
