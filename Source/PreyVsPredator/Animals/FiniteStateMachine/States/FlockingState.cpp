#include "FlockingState.h"


void UFlockingState::OnEnter(APreyController* AIOwner, UBlackboardComponent* BlackboardComponent)
{
	Super::OnEnter(AIOwner, BlackboardComponent);

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("Flocking State"));
}

void UFlockingState::Update(APreyController* AIOwner, UBlackboardComponent* BlackboardComponent, float DeltaTime)
{
	Super::Update(AIOwner, BlackboardComponent, DeltaTime);

	
}

void UFlockingState::OnExit(APreyController* AIOwner, UBlackboardComponent* BlackboardComponent)
{
	Super::OnExit(AIOwner, BlackboardComponent);
	
}
