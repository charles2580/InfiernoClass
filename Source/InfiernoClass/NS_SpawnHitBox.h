// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "HitBox.h"
#include "NS_SpawnHitBox.generated.h"

/**
 * 
 */

// // 콜리더 타입 열거형 (예: 박스 또는 스피어)
//UENUM(BlueprintType)
//enum class EColliderType : uint8
//{
//	Box     UMETA(DisplayName = "Box"),
//	Sphere  UMETA(DisplayName = "Sphere")
//};
//
//// 공격 타입 열거형 (예: 일반, 스턴, 에어본 등)
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
//	// 에디터에서 설정할 Hitbox 액터 클래스
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		TSubclassOf<AHitBox> HitboxActorClass;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		FName SpawnSocketName = NAME_None;
//
//	// Hitbox 생성 시 적용할 오프셋 (스켈레탈 메시 컴포넌트 기준)
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		FVector HitboxOffset;
//
//	// Hitbox의 크기 (박스의 경우 Extent, 스피어의 경우 반지름 등)
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		FVector HitboxSize;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		EColliderType ColliderType;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		EAttackType AttackType;
//
//	// 공격 타입, 데미지, 스턴 시간, 에어본 시간 등 추가 정보 (ACustomHitboxActor에서 이 값들을 사용하도록 구현)
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
//	// Spawn한 Hitbox 액터를 저장합니다.
//	UPROPERTY()
//	AHitBox* SpawnedHitboxActor;
};
