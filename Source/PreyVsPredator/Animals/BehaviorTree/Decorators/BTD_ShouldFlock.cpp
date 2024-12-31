#include "BTD_ShouldFlock.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTD_ShouldFlock::UBTD_ShouldFlock()
{
	ShouldFlockKey.AddBoolFilter(this, "ShouldFlock");
	ReachedDestinationKey.AddBoolFilter(this, "ReachedDestination");
}

bool UBTD_ShouldFlock::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* BlackboardComponent{OwnerComp.GetBlackboardComponent()};
	const bool ShouldFlock{BlackboardComponent->GetValueAsBool(ShouldFlockKey.SelectedKeyName)};
	
	if (ShouldFlock)
	{
		// Only reset if entity should flock
		BlackboardComponent->ClearValue(ShouldFlockKey.SelectedKeyName);
		BlackboardComponent->ClearValue(ReachedDestinationKey.SelectedKeyName);
	}
	
	return ShouldFlock;
}
