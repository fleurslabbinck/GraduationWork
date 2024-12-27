#include "BTT_ConsumeType.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseController.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"
#include "PreyVsPredator/InfluenceMaps/WorldGridSubsystem.h"


UBTT_ConsumeType::UBTT_ConsumeType()
{
	bNotifyTick = false;

	ConsumeLocationKey.AddVectorFilter(this, "ConsumeLocation");
}

EBTNodeResult::Type UBTT_ConsumeType::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ConsumeType(&OwnerComp);
	
	return EBTNodeResult::InProgress;
}

void UBTT_ConsumeType::ConsumeType(UBehaviorTreeComponent* OwnerComp)
{
	ABaseController* BaseController{Cast<ABaseController>(OwnerComp->GetAIOwner())};
	if (BaseController == nullptr) return FinishLatentAbort(*OwnerComp);

	ABaseEntity* Entity{Cast<ABaseEntity>(BaseController->GetPawn())};
	if (Entity == nullptr) return FinishLatentAbort(*OwnerComp);
	
	// Try to consume cell
	const UWorldGridSubsystem* WorldGrid{GetWorld()->GetSubsystem<UWorldGridSubsystem>()};
	const FVector ConsumeLocation{OwnerComp->GetBlackboardComponent()->GetValueAsVector(ConsumeLocationKey.SelectedKeyName)};
	
	if (WorldGrid->AttemptConsumption(ConsumeLocation, TargetType))
	{
		Entity->Consume(TargetType);
		BaseController->SetTimer(FTimerDelegate::CreateUObject(this, &UBTT_ConsumeType::ConsumeType, OwnerComp), EatTime);
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("eating grass"));
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