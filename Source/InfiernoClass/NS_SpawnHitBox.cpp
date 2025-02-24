// Fill out your copyright notice in the Description page of Project Settings.

#include "NS_SpawnHitBox.h"

void UNS_SpawnHitBox::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{

	// ���̷�Ż �޽� ������Ʈ�� ���� Transform�� �������� ������ ����
	FTransform MeshTransform = MeshComp->GetComponentTransform();
	MeshTransform.AddToTranslation(HitboxOffset);

	// Hitbox ���͸� SpawnActorDeferred�� ����
	AHitBox* Hitbox = MeshComp->GetWorld()->SpawnActorDeferred<AHitBox>(HitboxActorClass, MeshTransform);
	if (Hitbox)
	{
		// �����Ϳ��� ������ ���� Hitbox ���Ϳ� �����մϴ�.
		Hitbox->ColliderOffset = HitboxOffset;
		Hitbox->ColliderSize = HitboxSize;
		Hitbox->ColliderType = ColliderType;
		Hitbox->AttackType = AttackType;
		Hitbox->Damage = Damage;
		Hitbox->StunTime = StunTime;
		Hitbox->AirborneTime = AirborneTime;

		// Spawn�� �Ϸ�
		Hitbox->FinishSpawning(MeshTransform);

		// ������ ���͸� ���� (Notify End �� ����)
		SpawnedHitboxActor = Hitbox;
	}
}

void UNS_SpawnHitBox::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	// Notify ���� �� Spawn�� Hitbox ���Ͱ� �ִٸ� �����մϴ�.
	if (SpawnedHitboxActor)
	{
		SpawnedHitboxActor->Destroy();
		SpawnedHitboxActor = nullptr;
	}
}
