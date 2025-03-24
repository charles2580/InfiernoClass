// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HitboxComponent.generated.h"

/**
 * 
 */

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INFIERNOCLASS_API UHitboxComponent : public USceneComponent
{
	GENERATED_BODY()
	
public:
	UHitboxComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		FVector ColliderSize = FVector(20.0f, 20.0f, 20.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float Duration = 0.2f;

	void ActivateHitbox(FVector Location);
	void DeactivateHitbox();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hitbox")
		class UBoxComponent* Collider;

private:
	FTimerHandle TimerHandle;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* Overlapped, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	//void CreateCollider();
	void ConfigureCollision();
};
