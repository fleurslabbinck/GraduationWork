#include "StopFlockingCondition.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseController.h"

bool UStopFlockingCondition::Evaluate(UBlackboardComponent* BlackboardComponent) const
{
	bool ReachedDestination{false};
	
	if (const ABaseController* BaseController{Cast<ABaseController>(BlackboardComponent->GetOwner())}; BaseController != nullptr)
	{
		// Get blackboard value
		ReachedDestination = BlackboardComponent->GetValueAsBool(BaseController->GetReachedDestinationKeyName());
	}

	return ReachedDestination;
}
