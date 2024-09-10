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
