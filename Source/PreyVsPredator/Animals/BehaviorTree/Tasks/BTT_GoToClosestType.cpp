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
	if (MoveToClosestTarget(OwnerComp)) return EBTNodeResult::InProgress;
	return EBTNodeResult::Aborted;
}

bool UBTT_GoToClosestType::MoveToClosestTarget(const UBehaviorTreeComponent& OwnerComp) const
{
	bool bSuccess{false};

	if (AAIController* Controller{OwnerComp.GetAIOwner()}; Controller != nullptr)
	{
		UWorldGridSubsystem* WorldGrid{GetWorld()->GetSubsystem<UWorldGridSubsystem>()};

		// Get next target type cell from world grid
		const FVector CurrentPosition{Controller->GetPawn()->GetActorLocation()};
		const FVector GrassPatchLocation{WorldGrid->NextCellPosition(CurrentPosition, TargetType)};

		// Move pawn towards closest available target type cell
		bSuccess = Controller->MoveToLocation(GrassPatchLocation, WorldGrid->AcceptanceRadius()) != EPathFollowingRequestResult::Failed;
	}

	return bSuccess;
}

void UBTT_GoToClosestType::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const AAIController* Controller{OwnerComp.GetAIOwner()};
	if (Controller == nullptr) FinishLatentAbort(OwnerComp);

	if (Controller->GetMoveStatus() == EPathFollowingStatus::Type::Idle)
	{
		const UWorldGridSubsystem* WorldGrid{GetWorld()->GetSubsystem<UWorldGridSubsystem>()};
		const UWorldGridCell* CurrentCell{WorldGrid->CellAtPosition(Controller->GetPawn()->GetActorLocation())};
		if (CurrentCell != nullptr)
		{
			// if cell has target type, succeed
			if (CurrentCell->WorldType() == TargetType && CurrentCell->Available())
			{
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return;
			}
		}

		if (!MoveToClosestTarget(OwnerComp))
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}
	}
}
