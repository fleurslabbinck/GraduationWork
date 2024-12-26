#include "FlockingState.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseController.h"

void UFlockingState::InitializeState(AAIController* AIController, UBehaviorTree* BehaviorTree)
{
	Super::InitializeState(AIController, BehaviorTree);

	ABaseController* BaseController{Cast<ABaseController>(AIController)};
	if (BaseController != nullptr)
	{
		m_ReachedDestinationKeyName = BaseController->GetReachedDestinationKeyName();
	}
}

void UFlockingState::OnEnter(UBlackboardComponent* BlackboardComponent)
{
	Super::OnEnter(BlackboardComponent);

	BlackboardComponent->ClearValue(m_ReachedDestinationKeyName);
	
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("Flocking State"));
}