#include "BTT_GoToClosestGrassPatch.h"

#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "PreyVsPredator/InfluenceMaps/WorldGridSubsystem.h"


UBTT_GoToClosestGrassPatch::UBTT_GoToClosestGrassPatch()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTT_GoToClosestGrassPatch::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller{OwnerComp.GetAIOwner()};
	if (Controller == nullptr) return EBTNodeResult::Aborted;

	UWorldGridSubsystem* WorldGrid{GetWorld()->GetSubsystem<UWorldGridSubsystem>()};

	// Get next grass patch from world grid
	const FVector CurrentPosition{Controller->GetPawn()->GetActorLocation()};
	const UGridCell* GrassPatchCell{WorldGrid->NextGrassCell(CurrentPosition)};
	if (GrassPatchCell == nullptr) return EBTNodeResult::Aborted;
	
	const FVector GrassPatchLocation{GrassPatchCell->CenterPosition()};

	// Move pawn towards closest available grass patch
	const EPathFollowingRequestResult::Type Result{Controller->MoveToLocation(GrassPatchLocation, WorldGrid->AcceptenceRadius())};
	if (Result == EPathFollowingRequestResult::Failed)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("Failed"));
	}
	
	return EBTNodeResult::InProgress;
}

void UBTT_GoToClosestGrassPatch::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* Controller{OwnerComp.GetAIOwner()};
	if (Controller == nullptr) FinishLatentAbort(OwnerComp);

	if (Controller->GetMoveStatus() == EPathFollowingStatus::Type::Idle)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}