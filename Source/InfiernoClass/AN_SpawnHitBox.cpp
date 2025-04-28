// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_SpawnHitBox.h"

void UAN_SpawnHitBox::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp || !MeshComp->GetOwner())
	{
		return;
	}
	AActor* Owner = MeshComp->GetOwner();
	FVector Start = MeshComp->GetSocketLocation(SocketName);
	FVector End = Start + Owner->GetActorForwardVector()*AttackRange;
	float CapsuleHalfHeight = (End - Start).Size() * 0.5f;

	// �߰� ���� = ĸ�� �߽�
	FVector CapsuleCenter = (Start + End) * 0.5f;

	// ���� ȸ��
	FQuat CapsuleRotation = FRotationMatrix::MakeFromZ(End - Start).ToQuat();

	FCollisionShape CapsuleShape = FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Owner);

	TArray<FHitResult> HitResults;

	bool bHit = MeshComp->GetWorld()->SweepMultiByChannel(
		HitResults,
		CapsuleCenter,
		CapsuleCenter, // ������ ĸ��
		CapsuleRotation,
		ECC_Pawn, // �Ǵ� Ŀ���� ä��
		CapsuleShape,
		Params
	);

	for (const FHitResult& Hit : HitResults)
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			if (HitActor != Owner)
			{
				UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *HitActor->GetName());
				if (ABaseCharacter* Target = Cast<ABaseCharacter>(HitActor))
				{
					bool bHitSuccessful = Target->ApplyDamage(Damage, AttackType);
					if (bHitSuccessful)
					{
						FVector SpawnLoc = Start;
						UNiagaraFunctionLibrary::SpawnSystemAtLocation(MeshComp->GetWorld(), AttackEffect, SpawnLoc);
					}
				}
			}
		}
	}
}
