// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_SpawnHitBox.h"
#include "BaseCharacter.h"

void UAN_SpawnHitBox::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp)
	{
		return;
	}
	
	ABaseCharacter* Character = Cast<ABaseCharacter>(MeshComp->GetOwner());
	if (!Character || !Character->HitboxComponent)
	{
		return;
	}
	// 히트박스 설정
	UHitboxComponent* Hitbox = Character->HitboxComponent;
	Hitbox->ColliderSize = ColliderSize;
	Hitbox->Damage = Damage;
	Hitbox->Duration = Duration;

	// 소켓 기준 위치 계산
	if (SocketName != NAME_None && MeshComp->DoesSocketExist(SocketName))
	{
		FVector SocketLocation = MeshComp->GetSocketLocation(SocketName);
		Hitbox->ActivateHitbox(SocketLocation);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AnimNotify_ActivateHitbox: Invalid socket '%s'."), *SocketName.ToString());
	}
}
