#include "GrazingState.h"

#include "GameFramework/CharacterMovementComponent.h"


void UGrazingState::OnEnter(UBlackboardComponent* BlackboardComponent)
{
	Super::OnEnter(BlackboardComponent);

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("Grazing State"));
}

void UGrazingState::UpdateMaxSpeed()
{
	if (m_CharacterMovement == nullptr) return;
	m_CharacterMovement->MaxWalkSpeed = GrazingSpeed;
}
