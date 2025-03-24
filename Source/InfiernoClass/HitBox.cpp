// Fill out your copyright notice in the Description page of Project Settings.


#include "HitBox.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"

//// Sets default values
//AHitBox::AHitBox()
//{
// 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//
//	// ��Ʈ ������Ʈ ���� (���� SceneComponent ���)
//	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
//	RootComponent = Root;
//
//	// �⺻�� ����
//	ColliderType = EColliderType::Box;
//	ColliderOffset = FVector::ZeroVector;
//	ColliderSize = FVector(50.f, 50.f, 50.f);
//	AttackType = EAttackType::Normal;
//	Damage = 10.f;
//	StunTime = 0.f;
//	AirborneTime = 0.f;
//
//	ColliderComponent = nullptr;
//}
//
//// Called when the game starts or when spawned
//void AHitBox::BeginPlay()
//{
//	Super::BeginPlay();
//
//	if (ColliderComponent)
//	{
//		ColliderComponent->SetHiddenInGame(false);         // ���� �߿� ������ ����
//		ColliderComponent->SetVisibility(true);            // ���̵��� ����
//		UE_LOG(LogTemp, Warning, TEXT("collider is correct"));
//	}
//}
//
//void AHitBox::OnConstruction(const FTransform& Transform)
//{
//	Super::OnConstruction(Transform);
//
//	CreateColliderComponent();
//	if (ColliderComponent)
//	{
//		ColliderComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//		FTimerHandle TimerHandle;
//		GetWorldTimerManager().SetTimer(TimerHandle, [this]()
//			{
//				if (ColliderComponent)
//				{
//					ColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
//					UE_LOG(LogTemp, Warning, TEXT("Hitbox Collider Re-enabled"));
//				}
//			}, 0.1f, false);
//	}
//	UE_LOG(LogTemp, Warning, TEXT("HitBox is Spawned"));
//}
//
//// Called every frame
//void AHitBox::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
//void AHitBox::CreateColliderComponent()
//{
//	// ������ ������ ColliderComponent�� ������ ����
//	if (ColliderComponent)
//	{
//		ColliderComponent->DestroyComponent();
//		ColliderComponent = nullptr;
//	}
//
//	// ColliderOffset�� ������ ���ο� Transform ���
//	FTransform ColliderTransform = FTransform(FRotator::ZeroRotator, ColliderOffset, FVector(1.f));
//
//	// ColliderType�� ���� UBoxComponent �Ǵ� USphereComponent ����
//	switch (ColliderType)
//	{
//	case EColliderType::Box:
//	{
//		UBoxComponent* BoxComp = NewObject<UBoxComponent>(this, UBoxComponent::StaticClass(), TEXT("CustomBoxCollider"));
//		if (BoxComp)
//		{
//			BoxComp->RegisterComponent();
//			BoxComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
//			BoxComp->InitBoxExtent(ColliderSize); // ColliderSize�� Extent�� ����
//			BoxComp->SetRelativeTransform(ColliderTransform);
//			// ���ϴ� Collision ����: ���� ���, CustomCollision ä�� ���
//			BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
//			BoxComp->SetCollisionObjectType(ECC_GameTraceChannel1); // Hitbox ä�� (�´� ��ȣ�� ��ü)
//			BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
//			BoxComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // �÷��̾� ����
//
//			BoxComp->SetGenerateOverlapEvents(true);
//			BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AHitBox::OnHitboxOverlapBegin);
//
//			ColliderComponent = BoxComp;
//		}
//		break;
//	}
//	case EColliderType::Sphere:
//	{
//		USphereComponent* SphereComp = NewObject<USphereComponent>(this, USphereComponent::StaticClass(), TEXT("CustomSphereCollider"));
//		if (SphereComp)
//		{
//			SphereComp->RegisterComponent();
//			SphereComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
//			// ColliderSize�� X���� ���������� ��� (�Ϲ������� �����ؾ� ��)
//			SphereComp->SetSphereRadius(ColliderSize.X);
//			SphereComp->SetRelativeTransform(ColliderTransform);
//			SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
//			SphereComp->SetCollisionObjectType(ECC_GameTraceChannel1); // Hitbox ä�� (�´� ��ȣ�� ��ü)
//			SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
//			SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // �÷��̾� ����
//
//			SphereComp->SetGenerateOverlapEvents(true);
//			SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AHitBox::OnHitboxOverlapBegin);
//
//			ColliderComponent = SphereComp;
//		}
//		break;
//	}
//	default:
//		break;
//	}
//}
//
//void AHitBox::OnHitboxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
//	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	if (!OtherActor || OtherActor == this || OtherActor == OwnerCharacter)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("collider is ignore"));
//		return;
//	}
//
//	ABaseCharacter* TargetCharacter = Cast<ABaseCharacter>(OtherActor);
//	if (TargetCharacter)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("applyDamage"));
//		TargetCharacter->ApplyDamage(Damage);
//	}
//
//}

