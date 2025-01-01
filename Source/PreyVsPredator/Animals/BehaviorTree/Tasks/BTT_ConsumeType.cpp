#include "BTT_ConsumeType.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseController.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"
#include "PreyVsPredator/InfluenceMaps/WorldGridSubsystem.h"


UBTT_ConsumeType::UBTT_ConsumeType()
{
	bNotifyTick = true;

	ShouldFlockKey.AddBoolFilter(this, "ShouldFlock");
	ThirstyKey.AddBoolFilter(this, "Thirsty");
	ConsumeLocationKey.AddVectorFilter(this, "ConsumeLocation");
}

EBTNodeResult::Type UBTT_ConsumeType::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABaseController* BaseController{Cast<ABaseController>(OwnerComp.GetAIOwner())};
	if (BaseController != nullptr)
	{
		BaseController->SetTimer(FTimerDelegate::CreateUObject(this, &UBTT_ConsumeType::ConsumeType, &OwnerComp), ConsumeTime);
	}
	
	return EBTNodeResult::InProgress;
}

void UBTT_ConsumeType::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!PureBehaviorTree || TargetType == EWorldCellType::Water) return;
	
	// Fail if entity should flock or should drink
	UBlackboardComponent* BlackboardComponent{OwnerComp.GetBlackboardComponent()};
	if (BlackboardComponent->GetValueAsBool(ShouldFlockKey.SelectedKeyName) || BlackboardComponent->GetValueAsBool(ThirstyKey.SelectedKeyName))
	{
		// Stop timer to keep consuming
		if (ABaseController* BaseController{Cast<ABaseController>(OwnerComp.GetAIOwner())}; BaseController != nullptr)
		{
			BaseController->ResetTimer();

			if (ABaseEntity* Entity{Cast<ABaseEntity>(BaseController->GetPawn())}; Entity != nullptr)
			{
				// Unsubscribe from cell when done consuming
				const FVector ConsumeLocation{BlackboardComponent->GetValueAsVector(ConsumeLocationKey.SelectedKeyName)};
				if (UWorldGridCell* CurrentCell {GetWorld()->GetSubsystem<UWorldGridSubsystem>()->CellAtPosition(ConsumeLocation)}; CurrentCell != nullptr)
				{
					CurrentCell->Unsubscribe(Entity);
				}
	
				FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			}
		}
	}
}

void UBTT_ConsumeType::ConsumeType(UBehaviorTreeComponent* OwnerComp)
{
	ABaseController* BaseController{Cast<ABaseController>(OwnerComp->GetAIOwner())};
	if (BaseController == nullptr)
	{
		FinishLatentAbort(*OwnerComp);
		return;
	}

	ABaseEntity* Entity{Cast<ABaseEntity>(BaseController->GetPawn())};
	if (Entity == nullptr)
	{
		FinishLatentAbort(*OwnerComp);
		return;
	}	

	// Check if entity should keep going
	bool ShouldContinue{true};
	if (TargetType == EWorldCellType::Water && Entity->FullWater())
	{
		// Stop drinking water if full
		ShouldContinue = false;
	}
	
	// Try to consume cell
	const UWorldGridSubsystem* WorldGrid{GetWorld()->GetSubsystem<UWorldGridSubsystem>()};
	const FVector ConsumeLocation{OwnerComp->GetBlackboardComponent()->GetValueAsVector(ConsumeLocationKey.SelectedKeyName)};

	bool ConsumptionAttempt{WorldGrid->AttemptConsumption(ConsumeLocation, TargetType)};

	if (ConsumptionAttempt && ShouldContinue)
	{
		Entity->Consume(TargetType);
		BaseController->SetTimer(FTimerDelegate::CreateUObject(this, &UBTT_ConsumeType::ConsumeType, OwnerComp), ConsumeTime);
	}
	else if (!ConsumptionAttempt || !ShouldContinue)
	{
		// Unsubscribe from cell when done consuming
		if (UWorldGridCell* CurrentCell {WorldGrid->CellAtPosition(ConsumeLocation)}; CurrentCell != nullptr)
		{
			CurrentCell->Unsubscribe(Entity);
		}
		
		// Succeed if cell is fully consumed
		FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
	}
}
