// Fill out your copyright notice in the Description page of Project Settings.


#include "HitBox.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
AHitBox::AHitBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 루트 컴포넌트 생성 (보통 SceneComponent 사용)
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	// 기본값 설정
	ColliderType = EColliderType::Box;
	ColliderOffset = FVector::ZeroVector;
	ColliderSize = FVector(50.f, 50.f, 50.f);
	AttackType = EAttackType::Normal;
	Damage = 10.f;
	StunTime = 0.f;
	AirborneTime = 0.f;

	ColliderComponent = nullptr;
}

// Called when the game starts or when spawned
void AHitBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHitBox::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	CreateColliderComponent();
}

// Called every frame
void AHitBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHitBox::CreateColliderComponent()
{
	// 기존에 생성된 ColliderComponent가 있으면 제거
	if (ColliderComponent)
	{
		ColliderComponent->DestroyComponent();
		ColliderComponent = nullptr;
	}

	// ColliderOffset을 적용한 새로운 Transform 계산
	FTransform ColliderTransform = FTransform(FRotator::ZeroRotator, ColliderOffset, FVector(1.f));

	// ColliderType에 따라 UBoxComponent 또는 USphereComponent 생성
	switch (ColliderType)
	{
	case EColliderType::Box:
	{
		UBoxComponent* BoxComp = NewObject<UBoxComponent>(this, UBoxComponent::StaticClass(), TEXT("CustomBoxCollider"));
		if (BoxComp)
		{
			BoxComp->RegisterComponent();
			BoxComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
			BoxComp->InitBoxExtent(ColliderSize); // ColliderSize가 Extent로 사용됨
			BoxComp->SetRelativeTransform(ColliderTransform);
			// 원하는 Collision 설정: 예를 들어, CustomCollision 채널 사용
			BoxComp->SetCollisionProfileName(TEXT("BlockAll"));
			ColliderComponent = BoxComp;
		}
		break;
	}
	case EColliderType::Sphere:
	{
		USphereComponent* SphereComp = NewObject<USphereComponent>(this, USphereComponent::StaticClass(), TEXT("CustomSphereCollider"));
		if (SphereComp)
		{
			SphereComp->RegisterComponent();
			SphereComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
			// ColliderSize의 X값을 반지름으로 사용 (일반적으로 균일해야 함)
			SphereComp->SetSphereRadius(ColliderSize.X);
			SphereComp->SetRelativeTransform(ColliderTransform);
			SphereComp->SetCollisionProfileName(TEXT("BlockAll"));
			ColliderComponent = SphereComp;
		}
		break;
	}
	default:
		break;
	}
}

