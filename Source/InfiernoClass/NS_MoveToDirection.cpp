// Fill out your copyright notice in the Description page of Project Settings.


#include "NS_MoveToDirection.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/RootMotionSource.h"

void UNS_MoveToDirection::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!MeshComp || !Animation) return;

	ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
	if (!Character || !Character->GetCharacterMovement()) return;

	// Duration = Notify의 전체 시간
	float Duration = TotalDuration;

	// 이동 거리 계산
	float Distance = MoveSpeed * Duration;

	// 방향 설정
	FVector DirectionVector = (Direction == ERootMotionDirection::FORWARD)
		? Character->GetActorForwardVector()
		: -Character->GetActorForwardVector();

	// 시작 위치 및 타겟 위치 설정
	FVector StartLocation = Character->GetActorLocation();
	FVector TargetLocation = StartLocation + (DirectionVector * Distance);

	// RootMotion 생성
	TSharedPtr<FRootMotionSource_MoveToDynamicForce> MoveForce = MakeShared<FRootMotionSource_MoveToDynamicForce>();
	MoveForce->InstanceName = InstanceName;
	MoveForce->AccumulateMode = ERootMotionAccumulateMode::Override;
	MoveForce->Priority = 5;
	MoveForce->StartLocation = StartLocation;
	MoveForce->TargetLocation = TargetLocation;
	MoveForce->Duration = Duration;
	MoveForce->bRestrictSpeedToExpected = true;

	Character->GetCharacterMovement()->ApplyRootMotionSource(MoveForce);
}

void UNS_MoveToDirection::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (!MeshComp || !MeshComp->GetOwner()) return;

	ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
	if (!Character || !Character->GetCharacterMovement()) return;

	// 지정된 InstanceName으로 Root Motion 제거
	Character->GetCharacterMovement()->RemoveRootMotionSource(InstanceName);
}