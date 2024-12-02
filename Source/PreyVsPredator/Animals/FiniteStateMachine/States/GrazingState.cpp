#include "GrazingState.h"


void UGrazingState::OnEnter(APreyController* AIOwner, UBlackboardComponent* BlackboardComponent)
{
	Super::OnEnter(AIOwner, BlackboardComponent);

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("Grazing State"));
}

void UGrazingState::OnExit(APreyController* AIOwner, UBlackboardComponent* BlackboardComponent)
{
	Super::OnExit(AIOwner, BlackboardComponent);

	
}