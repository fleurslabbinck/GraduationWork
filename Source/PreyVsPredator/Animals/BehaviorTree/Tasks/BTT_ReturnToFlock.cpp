#include "BTT_ReturnToFlock.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"


UBTT_ReturnToFlock::UBTT_ReturnToFlock()
{
	bNotifyTick = true;

	FlockLocationKey.AddVectorFilter(this, "FlockLocation");
	ReachedDestinationKey.AddBoolFilter(this, "ReachedDestination");
}

EBTNodeResult::Type UBTT_ReturnToFlock::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIController* Controller{OwnerComp.GetAIOwner()}; Controller != nullptr)
	{
		// Get target from blackboard
		const FVector TargetLocation{OwnerComp.GetBlackboardComponent()->GetValueAsVector(FlockLocationKey.SelectedKeyName)};

		// Move entity back towards flock average position
		if (Controller->MoveToLocation(TargetLocation) != EPathFollowingRequestResult::Failed)
		{
			return EBTNodeResult::InProgress;
		}
	}

	return EBTNodeResult::Failed;
}

void UBTT_ReturnToFlock::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const AAIController* Controller{OwnerComp.GetAIOwner()};
	if (Controller == nullptr) FinishLatentAbort(OwnerComp);

	if (Controller->GetMoveStatus() == EPathFollowingStatus::Type::Idle)
	{
		// Reached destination when idle
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ReachedDestinationKey.SelectedKeyName, true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
