#include "BTT_ConsumeType.h"

#include "AIController.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseController.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"
#include "PreyVsPredator/InfluenceMaps/WorldGridSubsystem.h"


UBTT_ConsumeType::UBTT_ConsumeType()
{
	bNotifyTick = false;
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
	const FVector CurrentPosition{Entity->GetActorLocation()};
	
	if (GetWorld()->GetSubsystem<UWorldGridSubsystem>()->AttemptConsumption(CurrentPosition, TargetType))
	{
		Entity->Consume(TargetType);
		BaseController->SetTimer(FTimerDelegate::CreateUObject(this, &UBTT_ConsumeType::ConsumeType, OwnerComp), EatTime);
	}
	else
	{
		// Succeed if cell is fully consumed
		FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
	}
}