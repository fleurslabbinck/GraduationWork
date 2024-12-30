#include "DyingState.h"

void UDyingState::OnEnter(UBlackboardComponent* BlackboardComponent)
{
	Super::OnEnter(BlackboardComponent);

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("Dying State"));
}
