// Fill out your copyright notice in the Description page of Project Settings.

#include "NS_SpawnHitBox.h"
#include "BaseCharacter.h"

//void UNS_SpawnHitBox::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
//{
//	if (!MeshComp || !HitboxActorClass) 
//	{
//		return;
//	}
//
//	FTransform SpawnTransform;
//
//	if (SpawnSocketName != NAME_None && MeshComp->DoesSocketExist(SpawnSocketName))
//	{
//		SpawnTransform = MeshComp->GetSocketTransform(SpawnSocketName, RTS_World);
//	}
//	else
//	{
//		// ������ ���� ��� �⺻ �޽� ���� ��ġ + ������
//		SpawnTransform = MeshComp->GetComponentTransform();
//		SpawnTransform.AddToTranslation(HitboxOffset);
//	}
//
//
//	// Hitbox ���͸� SpawnActorDeferred�� ����
//	AHitBox* Hitbox = MeshComp->GetWorld()->SpawnActorDeferred<AHitBox>(HitboxActorClass, SpawnTransform);
//	if (Hitbox)
//	{
//		// �����Ϳ��� ������ ���� Hitbox ���Ϳ� �����մϴ�.
//		Hitbox->OwnerCharacter = Cast<ABaseCharacter>(MeshComp->GetOwner());
//		Hitbox->ColliderOffset = HitboxOffset;
//		Hitbox->ColliderSize = HitboxSize;
//		Hitbox->ColliderType = ColliderType;
//		Hitbox->AttackType = AttackType;
//		Hitbox->Damage = Damage;
//		Hitbox->StunTime = StunTime;
//		Hitbox->AirborneTime = AirborneTime;
//
//		// Spawn�� �Ϸ�
//		Hitbox->FinishSpawning(SpawnTransform);
//
//		// ������ ���͸� ���� (Notify End �� ����)
//		SpawnedHitboxActor = Hitbox;
//	}
//
//	//if (MeshComp->GetOwner())
//	//{
//	//	ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(MeshComp->GetOwner());
//	//	if (MyCharacter)
//	//	{
//	//		// ������ HitBox ������ Transform�� ��� ���� Ÿ������ ����
//	//		FTransform TargetTransform = Hitbox->GetActorTransform();
//	//		MyCharacter->SetWarpTarget(FName("AttackTarget"), TargetTransform);
//	//	}
//	//}
//
//}
//
//void UNS_SpawnHitBox::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
//{
//	// Notify ���� �� Spawn�� Hitbox ���Ͱ� �ִٸ� �����մϴ�.
//	if (SpawnedHitboxActor)
//	{
//		//SpawnedHitboxActor->Destroy();
//		//SpawnedHitboxActor = nullptr;
//	}
//
//	//if (MeshComp->GetOwner())
//	//{
//	//	ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(MeshComp->GetOwner());
//	//	if (MyCharacter)
//	//	{
//	//		MyCharacter->ClearWarpTarget(FName("AttackTarget"));
//	//	}
//	//}
//}
