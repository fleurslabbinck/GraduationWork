#include "BaseAnimInstance.h"

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	const APawn* Pawn{TryGetPawnOwner()};
	if (Pawn == nullptr) return;

	// Set pawn speed
	const FVector Velocity{Pawn->GetVelocity()};
	Speed = Velocity.Size();

	// Set pawn direction
	const FRotator PawnRotation{Pawn->GetActorForwardVector().Rotation()};
	const FRotator VelocityDirection{Velocity.ToOrientationRotator()};
	Direction = FMath::FindDeltaAngleDegrees(PawnRotation.Yaw, VelocityDirection.Yaw);
}
