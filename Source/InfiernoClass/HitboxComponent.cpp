// Fill out your copyright notice in the Description page of Project Settings.


#include "HitboxComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "BaseCharacter.h"
#include "TimerManager.h"

UHitboxComponent::UHitboxComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("HitboxCollider"));
	Collider->SetupAttachment(this);
	Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Collider->SetGenerateOverlapEvents(false);

	Collider->SetCollisionObjectType(ECC_GameTraceChannel1);
	Collider->SetCollisionResponseToAllChannels(ECR_Ignore);
	Collider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Collider->OnComponentBeginOverlap.AddDynamic(this, &UHitboxComponent::OnBeginOverlap);
	Collider->SetHiddenInGame(false);
}


void UHitboxComponent::ConfigureCollision()
{
	if (!Collider)
	{
		return;
	}

	Collider->SetBoxExtent(ColliderSize);
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collider->SetGenerateOverlapEvents(true);
}

void UHitboxComponent::ActivateHitbox(FVector Location)
{
	if (!Collider)
	{
		return;
	}
	Collider->SetWorldLocation(Location);
	ConfigureCollision();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UHitboxComponent::DeactivateHitbox, Duration, false);
}

void UHitboxComponent::DeactivateHitbox()
{
	if (Collider)
	{
		Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Collider->SetGenerateOverlapEvents(false);
	}
}

void UHitboxComponent::OnBeginOverlap(UPrimitiveComponent* Overlapped, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetOwner())
	{
		ABaseCharacter* Target = Cast<ABaseCharacter>(OtherActor);
		ABaseCharacter* OwnerCharacter = Cast<ABaseCharacter>(GetOwner());

		if (Target && OwnerCharacter && Target != OwnerCharacter)
		{
			Target->ApplyDamage(Damage);
			UE_LOG(LogTemp, Warning, TEXT("Hitbox damaged %s for %.1f"), *Target->GetName(), Damage);
		}
	}
}