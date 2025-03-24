// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "HitBox.h"
#include "NS_SpawnHitBox.generated.h"

/**
 * 
 */

// // �ݸ��� Ÿ�� ������ (��: �ڽ� �Ǵ� ���Ǿ�)
//UENUM(BlueprintType)
//enum class EColliderType : uint8
//{
//	Box     UMETA(DisplayName = "Box"),
//	Sphere  UMETA(DisplayName = "Sphere")
//};
//
//// ���� Ÿ�� ������ (��: �Ϲ�, ����, ��� ��)
//UENUM(BlueprintType)
//enum class EAttackType : uint8
//{
//	Normal   UMETA(DisplayName = "Normal"),
//	Stun     UMETA(DisplayName = "Stun"),
//	Airborne UMETA(DisplayName = "Airborne")
//};

UCLASS()
class INFIERNOCLASS_API UNS_SpawnHitBox : public UAnimNotifyState
{
	GENERATED_BODY()
	
//public:
//	// �����Ϳ��� ������ Hitbox ���� Ŭ����
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		TSubclassOf<AHitBox> HitboxActorClass;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		FName SpawnSocketName = NAME_None;
//
//	// Hitbox ���� �� ������ ������ (���̷�Ż �޽� ������Ʈ ����)
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		FVector HitboxOffset;
//
//	// Hitbox�� ũ�� (�ڽ��� ��� Extent, ���Ǿ��� ��� ������ ��)
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		FVector HitboxSize;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		EColliderType ColliderType;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		EAttackType AttackType;
//
//	// ���� Ÿ��, ������, ���� �ð�, ��� �ð� �� �߰� ���� (ACustomHitboxActor���� �� ������ ����ϵ��� ����)
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		float Damage;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		float StunTime;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		float AirborneTime;
//
//
//	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
//		float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
//
//	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
//		const FAnimNotifyEventReference& EventReference);
//
//private:
//	// Spawn�� Hitbox ���͸� �����մϴ�.
//	UPROPERTY()
//	AHitBox* SpawnedHitboxActor;
};
