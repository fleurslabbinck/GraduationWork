#include "FlockingState.h"

void UFlockingState::OnEnter(UBlackboardComponent* BlackboardComponent)
{
	Super::OnEnter(BlackboardComponent);
	
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("Flocking State"));
}