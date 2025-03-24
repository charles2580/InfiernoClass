// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "HitboxComponent.h"
#include "AN_SpawnHitBox.generated.h"

/**
 * 
 */
UCLASS()
class INFIERNOCLASS_API UAN_SpawnHitBox : public UAnimNotify
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		FName SocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector ColliderSize = FVector(30.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector RelativeLocation = FVector(0.f, 0.f, 50.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Duration = 0.3f;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
