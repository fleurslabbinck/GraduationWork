#include "HydratingState.h"

#include "GameFramework/CharacterMovementComponent.h"

void UHydratingState::OnEnter(UBlackboardComponent* BlackboardComponent)
{
	Super::OnEnter(BlackboardComponent);

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("Hydrating State"));
}

void UHydratingState::UpdateMaxSpeed()
{
	if (m_CharacterMovement == nullptr) return;
	m_CharacterMovement->MaxWalkSpeed = HydratingSpeed;
}
