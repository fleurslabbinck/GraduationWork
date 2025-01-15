#include "BTT_ConsumeType.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseController.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"
#include "PreyVsPredator/InfluenceMaps/WorldGridSubsystem.h"


UBTT_ConsumeType::UBTT_ConsumeType()
{
	bNotifyTaskFinished = true;
	
	ConsumeLocationKey.AddVectorFilter(this, "ConsumeLocation");
}

void UBTT_ConsumeType::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	if (const AAIController* Controller{Cast<AAIController>(OwnerComp.GetAIOwner())}; Controller != nullptr)
	{
		if (ABaseEntity* Entity{Cast<ABaseEntity>(Controller->GetPawn())}; Entity != nullptr)
		{
			const UWorldGridSubsystem* WorldGrid{GetWorld()->GetSubsystem<UWorldGridSubsystem>()};
	
			// Unsubscribe from cell when done consuming
			const FVector ConsumeLocation{OwnerComp.GetBlackboardComponent()->GetValueAsVector(ConsumeLocationKey.SelectedKeyName)};
			if (UWorldGridCell* CurrentCell {WorldGrid->CellAtPosition(ConsumeLocation)}; CurrentCell != nullptr)
			{
				CurrentCell->Unsubscribe(Entity);
			}
		}
	}
}

EBTNodeResult::Type UBTT_ConsumeType::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABaseController* BaseController{Cast<ABaseController>(OwnerComp.GetAIOwner())};
	if (BaseController != nullptr)
	{
		// Start consumption
		BaseController->SetTimer(FTimerDelegate::CreateUObject(this, &UBTT_ConsumeType::ConsumeType, &OwnerComp), ConsumeTime);

		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Aborted;
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
		// Succeed if cell is fully consumed or should stop continuing
		FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
	}
}
