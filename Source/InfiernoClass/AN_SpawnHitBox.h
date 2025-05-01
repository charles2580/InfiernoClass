// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "HitboxComponent.h"
#include "BaseCharacter.h"
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
		float CapsuleRadius = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AttackRange = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isAirborneAttack = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAttackType AttackType = EAttackType::Mid;

	UPROPERTY(EditAnywhere, Category = "Animation")
		UNiagaraSystem* AttackEffect;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
