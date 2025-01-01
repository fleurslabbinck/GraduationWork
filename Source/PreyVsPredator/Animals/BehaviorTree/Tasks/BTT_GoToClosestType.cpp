#include "BTT_GoToClosestType.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"
#include "PreyVsPredator/Animals/Flocking/BaseFlock.h"
#include "PreyVsPredator/InfluenceMaps/WorldGridSubsystem.h"


UBTT_GoToClosestType::UBTT_GoToClosestType()
{
	bNotifyTick = true;

	ShouldFlockKey.AddBoolFilter(this, "ShouldFlock");
	ThirstyKey.AddBoolFilter(this, "Thirsty");
	ConsumeLocationKey.AddVectorFilter(this, "ConsumeLocation");
}

EBTNodeResult::Type UBTT_GoToClosestType::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (MoveToClosestTarget(OwnerComp)) return EBTNodeResult::InProgress;
	return EBTNodeResult::Failed;
}

bool UBTT_GoToClosestType::MoveToClosestTarget(UBehaviorTreeComponent& OwnerComp) const
{
	bool bSuccess{false};

	if (AAIController* Controller{OwnerComp.GetAIOwner()}; Controller != nullptr)
	{
		ABaseEntity* Entity{Cast<ABaseEntity>(Controller->GetPawn())};
		if (Entity != nullptr)
		{
			const UWorldGridSubsystem* WorldGrid{GetWorld()->GetSubsystem<UWorldGridSubsystem>()};
			
			// Get next target type cell from world grid
			FVector TargetLocation;

			if (const ABaseFlock* Flock{Entity->Flock()}; Flock != nullptr)
			{
				// Influence by flock location if entity is in flock
				TargetLocation = (Flock->FlockLocation() + Entity->GetActorLocation()) / 2.f;
			}
			else
			{
				TargetLocation = Entity->GetActorLocation();
			}
			
			const FVector GrassPatchLocation{WorldGrid->NextCellPosition(TargetLocation, TargetType)};
			
			if (GrassPatchLocation == FVector::ZeroVector)
			{
				// If no valid next location, return false
				return bSuccess;
			}

			// Set consume location in blackboard
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(ConsumeLocationKey.SelectedKeyName, GrassPatchLocation);

			// Move pawn towards closest available target type cell
			bSuccess = Controller->MoveToLocation(GrassPatchLocation, WorldGrid->AcceptanceRadius()) != EPathFollowingRequestResult::Failed;
		}
	}

	return bSuccess;
}

void UBTT_GoToClosestType::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const AAIController* Controller{OwnerComp.GetAIOwner()};
	if (Controller == nullptr)
	{
		FinishLatentAbort(OwnerComp);
		return;
	}

	if (PureBehaviorTree && TargetType != EWorldCellType::Water)
	{
		// Fail if entity should flock or should drink
		UBlackboardComponent* BlackboardComponent{OwnerComp.GetBlackboardComponent()};
		if (BlackboardComponent->GetValueAsBool(ShouldFlockKey.SelectedKeyName) || BlackboardComponent->GetValueAsBool(ThirstyKey.SelectedKeyName))
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return;
		}
	}

	if (Controller->GetMoveStatus() == EPathFollowingStatus::Type::Idle)
	{
		if (APawn* EntityPawn{Cast<APawn>(Controller->GetPawn())}; EntityPawn != nullptr)
		{
			const UWorldGridSubsystem* WorldGrid{GetWorld()->GetSubsystem<UWorldGridSubsystem>()};
			UWorldGridCell* CurrentCell{WorldGrid->CellAtPosition(Controller->GetPawn()->GetActorLocation())};
			if (CurrentCell != nullptr)
			{
				// if cell has target type, succeed
				if (CurrentCell->WorldType() == TargetType && CurrentCell->Available())
				{
					// Subscribe to cell
					CurrentCell->Subscribe(EntityPawn);

					// Succeed task
					FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
					return;
				}
			}
		}

		// Fail if not valid
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
}
