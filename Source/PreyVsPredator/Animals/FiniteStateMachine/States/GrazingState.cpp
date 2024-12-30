#include "GrazingState.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PreyVsPredator/InfluenceMaps/WorldGridSubsystem.h"


UGrazingState::UGrazingState()
{
	m_MaxSpeed = m_MaxGrazingSpeed;
}

void UGrazingState::OnEnter(UBlackboardComponent* BlackboardComponent)
{
	Super::OnEnter(BlackboardComponent);

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("Grazing State"));
}

void UGrazingState::OnExit(UBlackboardComponent* BlackboardComponent)
{
	Super::OnExit(BlackboardComponent);

	// Make sure entity is unsubscribed from cell when changing state
	AActor* Entity{m_AIController->GetPawn()};
	UWorldGridCell* CurrentCell {GetOuter()->GetWorld()->GetSubsystem<UWorldGridSubsystem>()->CellAtPosition(BlackboardComponent->GetValueAsVector("ConsumeLocation"))};
	if (CurrentCell != nullptr)
	{
		CurrentCell->Unsubscribe(Entity);
	}
}