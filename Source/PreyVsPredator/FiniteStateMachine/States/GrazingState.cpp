#include "GrazingState.h"

#include "PreyVsPredator/Animals/Prey/PreyController.h"


void UGrazingState::OnEnter(APreyController* AIOwner, UBlackboardComponent* BlackboardComponent)
{
	Super::OnEnter(AIOwner, BlackboardComponent);

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("Grazing State"));
}

void UGrazingState::Update(APreyController* AIOwner, UBlackboardComponent* BlackboardComponent, float DeltaTime)
{
	Super::Update(AIOwner, BlackboardComponent, DeltaTime);

	APawn* Pawn{AIOwner->GetPawn()};
	const FVector TargetLocation{Pawn->GetActorForwardVector() + Pawn->GetActorRightVector()};
	Pawn->AddMovementInput(TargetLocation);
}

void UGrazingState::OnExit(APreyController* AIOwner, UBlackboardComponent* BlackboardComponent)
{
	Super::OnExit(AIOwner, BlackboardComponent);

	
}