// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_SetWarpTarget.h"
#include "BaseCharacter.h"

void UAN_SetWarpTarget::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp)
	{
		return;
	}

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner)
	{
		return;
	}

	ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(Owner);
	if (MyCharacter)
	{
		FTransform TargetTransform;
		TargetTransform.SetLocation(MyCharacter->GetActorLocation() + TargetLocation);

		MyCharacter->SetWarpTarget(WarpTargetName, TargetTransform);
	}
}