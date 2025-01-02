#include "PlayerAnimInstance.h"

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Pawn)
	{
		Pawn = TryGetPawnOwner();
	}
	ACharacter* Character = Cast<ACharacter>(Pawn);
	if (Character)
	{
		FVector Velocity = Character->GetVelocity();
		Speed = Velocity.Size();
		
	}
}

void UPlayerAnimInstance::AnimNotify_Jump()
{
	Pawn = TryGetPawnOwner();
	ACharacter* Character = Cast<ACharacter>(Pawn);
	if (Character)
	{
		Character->Jump();
		bIsJumping = true;
	}
}

void UPlayerAnimInstance::AnimNotify_JumpEnd()
{
	UE_LOG(LogTemp, Log, TEXT("Jump End"));
}
