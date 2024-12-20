#include "BTT_GoToClosestType.h"

#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "PreyVsPredator/InfluenceMaps/WorldGridSubsystem.h"


UBTT_GoToClosestType::UBTT_GoToClosestType()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTT_GoToClosestType::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller{OwnerComp.GetAIOwner()};
	if (Controller == nullptr) return EBTNodeResult::Aborted;

	UWorldGridSubsystem* WorldGrid{GetWorld()->GetSubsystem<UWorldGridSubsystem>()};

	// Get next grass patch from world grid
	const FVector CurrentPosition{Controller->GetPawn()->GetActorLocation()};
	const FVector GrassPatchLocation{WorldGrid->NextCellPosition(CurrentPosition, TargetType)};

	// Move pawn towards closest available grass patch
	const EPathFollowingRequestResult::Type Result{Controller->MoveToLocation(GrassPatchLocation, WorldGrid->AcceptanceRadius())};
	if (Result == EPathFollowingRequestResult::Failed)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("Failed"));
	}
	
	return EBTNodeResult::InProgress;
}

void UBTT_GoToClosestType::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* Controller{OwnerComp.GetAIOwner()};
	if (Controller == nullptr) FinishLatentAbort(OwnerComp);

	if (Controller->GetMoveStatus() == EPathFollowingStatus::Type::Idle)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}