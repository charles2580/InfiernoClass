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
//	// Hitbox�� �ݸ��� Ÿ�� (Box �Ǵ� Sphere)
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		EColliderType ColliderType;
//
//	// �ݸ��� ���� ������ (���� ����)
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		FVector ColliderOffset;
//
//	// �ݸ��� ũ��: �ڽ��� ��� Extent, ���Ǿ��� ��� ������
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		FVector ColliderSize;
//
//	// ���� Ÿ��
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		EAttackType AttackType;
//
//	// ������
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		float Damage;
//
//	// ���� �ð� (��)
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
//		float StunTime;
//
//	// ��� �ð� (��)
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
