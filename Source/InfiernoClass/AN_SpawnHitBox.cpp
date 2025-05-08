// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_SpawnHitBox.h"

void UAN_SpawnHitBox::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp || !MeshComp->GetOwner())
	{
		return;
	}
	ABaseCharacter* Owner = Cast<ABaseCharacter>(MeshComp->GetOwner());
	FVector Start = MeshComp->GetSocketLocation(SocketName);
	FVector End = Start + Owner->GetActorForwardVector()*AttackRange;
	float CapsuleHalfHeight = (End - Start).Size() * 0.5f;

	// Áß°£ ÁöÁ¡ = Ä¸½¶ Áß½É
	FVector CapsuleCenter = (Start + End) * 0.5f;

	// ¹æÇâ È¸Àü
	FQuat CapsuleRotation = FRotationMatrix::MakeFromZ(End - Start).ToQuat();

	FCollisionShape CapsuleShape = FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Owner);

	TArray<FHitResult> HitResults;

	bool bHit = MeshComp->GetWorld()->SweepMultiByChannel(
		HitResults,
		CapsuleCenter,
		CapsuleCenter, // Á¤ÁöµÈ Ä¸½¶
		CapsuleRotation,
		ECC_Pawn, // ¶Ç´Â Ä¿½ºÅÒ Ã¤³Î
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
					bool bHitSuccessful = Target->ApplyDamage(Damage, AttackType, isAirborneAttack);
					if (bHitSuccessful)
					{
						Owner->ApplyHitStop(0.1f);
						FVector SpawnLoc = Start;
						UNiagaraFunctionLibrary::SpawnSystemAtLocation(MeshComp->GetWorld(), AttackEffect, SpawnLoc);
						UE_LOG(LogTemp, Warning, TEXT("Attack Effect Spawn Success"));
					}
					return;
				}
			}
		}
	}
}
