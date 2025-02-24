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

	// ��Ʈ ������Ʈ ���� (���� SceneComponent ���)
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	// �⺻�� ����
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
	// ������ ������ ColliderComponent�� ������ ����
	if (ColliderComponent)
	{
		ColliderComponent->DestroyComponent();
		ColliderComponent = nullptr;
	}

	// ColliderOffset�� ������ ���ο� Transform ���
	FTransform ColliderTransform = FTransform(FRotator::ZeroRotator, ColliderOffset, FVector(1.f));

	// ColliderType�� ���� UBoxComponent �Ǵ� USphereComponent ����
	switch (ColliderType)
	{
	case EColliderType::Box:
	{
		UBoxComponent* BoxComp = NewObject<UBoxComponent>(this, UBoxComponent::StaticClass(), TEXT("CustomBoxCollider"));
		if (BoxComp)
		{
			BoxComp->RegisterComponent();
			BoxComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
			BoxComp->InitBoxExtent(ColliderSize); // ColliderSize�� Extent�� ����
			BoxComp->SetRelativeTransform(ColliderTransform);
			// ���ϴ� Collision ����: ���� ���, CustomCollision ä�� ���
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
			// ColliderSize�� X���� ���������� ��� (�Ϲ������� �����ؾ� ��)
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

