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
	ConsumeType(&OwnerComp);
	
	return EBTNodeResult::InProgress;
}

void UBTT_ConsumeType::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (PureBehaviorTree && TargetType != EWorldCellType::Water)
	{
		// Fail if entity should flock or should drink
		UBlackboardComponent* BlackboardComponent{OwnerComp.GetBlackboardComponent()};
		if (BlackboardComponent->GetValueAsBool(ShouldFlockKey.SelectedKeyName) || BlackboardComponent->GetValueAsBool(ThirstyKey.SelectedKeyName))
		{
			// Stop consuming entity
			ABaseController* BaseController{Cast<ABaseController>(OwnerComp.GetAIOwner())};
			if (BaseController != nullptr) BaseController->ResetTimer();
		
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}
	}
}

void UBTT_ConsumeType::ConsumeType(UBehaviorTreeComponent* OwnerComp)
{
	ABaseController* BaseController{Cast<ABaseController>(OwnerComp->GetAIOwner())};
	if (BaseController == nullptr) return FinishLatentAbort(*OwnerComp);

	ABaseEntity* Entity{Cast<ABaseEntity>(BaseController->GetPawn())};
	if (Entity == nullptr) return FinishLatentAbort(*OwnerComp);

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

	if (WorldGrid->AttemptConsumption(ConsumeLocation, TargetType) && ShouldContinue)
	{
		Entity->Consume(TargetType);
		BaseController->SetTimer(FTimerDelegate::CreateUObject(this, &UBTT_ConsumeType::ConsumeType, OwnerComp), ConsumeTime);
	}
	else
	{
		// Unsubscribe from cell when done eating
		if (UWorldGridCell* CurrentCell {WorldGrid->CellAtPosition(ConsumeLocation)}; CurrentCell != nullptr)
		{
			CurrentCell->Unsubscribe(Entity);
		}
		
		// Succeed if cell is fully consumed
		FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
	}
}
