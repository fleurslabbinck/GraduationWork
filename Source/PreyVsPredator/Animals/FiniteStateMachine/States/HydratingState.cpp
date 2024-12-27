#include "HydratingState.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PreyVsPredator/InfluenceMaps/WorldGridSubsystem.h"

class UWorldGridSubsystem;

void UHydratingState::OnEnter(UBlackboardComponent* BlackboardComponent)
{
	Super::OnEnter(BlackboardComponent);

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("Hydrating State"));
}

void UHydratingState::OnExit(UBlackboardComponent* BlackboardComponent)
{
	Super::OnExit(BlackboardComponent);

	// Make sure entity is unsubscribed from cell when changing state
	AActor* Entity{m_AIController->GetPawn()};
	UWorldGridCell* CurrentCell {GetWorld()->GetSubsystem<UWorldGridSubsystem>()->CellAtPosition(BlackboardComponent->GetValueAsVector("ConsumeLocation"))};
	if (CurrentCell != nullptr)
	{
		CurrentCell->Unsubscribe(Entity);
	}
}

void UHydratingState::UpdateMaxSpeed()
{
	if (m_CharacterMovement == nullptr) return;
	m_CharacterMovement->MaxWalkSpeed = HydratingSpeed;
}
