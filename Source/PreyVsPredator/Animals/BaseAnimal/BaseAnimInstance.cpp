#include "BaseAnimInstance.h"

#include "BaseEntity.h"


void UBaseAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	ABaseEntity* Entity{Cast<ABaseEntity>(TryGetPawnOwner())};
	if (Entity == nullptr) return;

	Entity->OnDeath.AddDynamic(this, &UBaseAnimInstance::SetDead);
}

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

void UBaseAnimInstance::SetDead()
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("Dead"));
	Dead = true;
}
