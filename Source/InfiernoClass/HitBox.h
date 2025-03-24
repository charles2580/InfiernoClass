// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseCharacter.h"
#include "HitBox.generated.h"


//UENUM(BlueprintType)
//enum class EColliderType : uint8
//{
//	Box     UMETA(DisplayName = "Box"),
//	Sphere  UMETA(DisplayName = "Sphere")
//};

//UENUM(BlueprintType)
//enum class EAttackType : uint8
//{
//	Normal   UMETA(DisplayName = "Normal"),
//	Stun     UMETA(DisplayName = "Stun"),
//	Airborne UMETA(DisplayName = "Airborne")
//};

UCLASS()
class INFIERNOCLASS_API AHitBox : public AActor
{
	GENERATED_BODY()
	
//public:	
//	// Sets default values for this actor's properties
//	AHitBox();
//
//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:	
//	virtual void OnConstruction(const FTransform& Transform) override;
//	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
//
//	// Hitbox의 콜리더 타입 (Box 또는 Sphere)
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		EColliderType ColliderType;
//
//	// 콜리더 생성 오프셋 (액터 기준)
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		FVector ColliderOffset;
//
//	// 콜리더 크기: 박스의 경우 Extent, 스피어의 경우 반지름
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		FVector ColliderSize;
//
//	// 공격 타입
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		EAttackType AttackType;
//
//	// 데미지
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		float Damage;
//
//	// 스턴 시간 (초)
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		float StunTime;
//
//	// 에어본 시간 (초)
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		float AirborneTime;
//
//	UPROPERTY(BlueprintReadWrite, Category = "Hitbox")
//	ABaseCharacter* OwnerCharacter;
//
//private:
//	UPROPERTY(EditAnywhere, Category = "Hitbox")
//	class UShapeComponent* ColliderComponent;
//
//	void CreateColliderComponent();
//	void OnHitboxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
//		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
