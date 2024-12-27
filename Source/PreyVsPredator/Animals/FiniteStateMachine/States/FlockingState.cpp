#include "FlockingState.h"

#include "BehaviorTree/BlackboardComponent.h"


void UFlockingState::OnEnter(UBlackboardComponent* BlackboardComponent)
{
	Super::OnEnter(BlackboardComponent);

	BlackboardComponent->ClearValue(m_ReachedDestinationKeyName);
	
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("Flocking State"));
}