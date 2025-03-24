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
//		// 소켓이 없을 경우 기본 메시 기준 위치 + 오프셋
//		SpawnTransform = MeshComp->GetComponentTransform();
//		SpawnTransform.AddToTranslation(HitboxOffset);
//	}
//
//
//	// Hitbox 액터를 SpawnActorDeferred로 생성
//	AHitBox* Hitbox = MeshComp->GetWorld()->SpawnActorDeferred<AHitBox>(HitboxActorClass, SpawnTransform);
//	if (Hitbox)
//	{
//		// 에디터에서 설정한 값을 Hitbox 액터에 전달합니다.
//		Hitbox->OwnerCharacter = Cast<ABaseCharacter>(MeshComp->GetOwner());
//		Hitbox->ColliderOffset = HitboxOffset;
//		Hitbox->ColliderSize = HitboxSize;
//		Hitbox->ColliderType = ColliderType;
//		Hitbox->AttackType = AttackType;
//		Hitbox->Damage = Damage;
//		Hitbox->StunTime = StunTime;
//		Hitbox->AirborneTime = AirborneTime;
//
//		// Spawn을 완료
//		Hitbox->FinishSpawning(SpawnTransform);
//
//		// 생성한 액터를 저장 (Notify End 시 제거)
//		SpawnedHitboxActor = Hitbox;
//	}
//
//	//if (MeshComp->GetOwner())
//	//{
//	//	ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(MeshComp->GetOwner());
//	//	if (MyCharacter)
//	//	{
//	//		// 생성된 HitBox 액터의 Transform을 모션 워핑 타겟으로 설정
//	//		FTransform TargetTransform = Hitbox->GetActorTransform();
//	//		MyCharacter->SetWarpTarget(FName("AttackTarget"), TargetTransform);
//	//	}
//	//}
//
//}
//
//void UNS_SpawnHitBox::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
//{
//	// Notify 종료 시 Spawn한 Hitbox 액터가 있다면 제거합니다.
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
