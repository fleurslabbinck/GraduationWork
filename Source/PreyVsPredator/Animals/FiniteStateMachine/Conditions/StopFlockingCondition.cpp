#include "StopFlockingCondition.h"

#include "BehaviorTree/BlackboardComponent.h"

FName UStopFlockingCondition::ReachedDestinationName{"ReachedDestination"};

bool UStopFlockingCondition::Evaluate(UBlackboardComponent* BlackboardComponent) const
{
	return BlackboardComponent->GetValueAsBool(ReachedDestinationName);
}
