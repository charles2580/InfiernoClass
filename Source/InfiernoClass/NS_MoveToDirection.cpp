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

	// Duration = Notify�� ��ü �ð�
	float Duration = TotalDuration;

	// �̵� �Ÿ� ���
	float Distance = MoveSpeed * Duration;

	// ���� ����
	FVector DirectionVector = (Direction == ERootMotionDirection::FORWARD)
		? Character->GetActorForwardVector()
		: -Character->GetActorForwardVector();

	// ���� ��ġ �� Ÿ�� ��ġ ����
	FVector StartLocation = Character->GetActorLocation();
	FVector TargetLocation = StartLocation + (DirectionVector * Distance);

	// RootMotion ����
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

	// ������ InstanceName���� Root Motion ����
	Character->GetCharacterMovement()->RemoveRootMotionSource(InstanceName);
}