#include "BTT_DestroyEntity.h"

#include "PreyVsPredator/Animals/BaseAnimal/BaseController.h"
#include "PreyVsPredator/Animals/Subsystems/WorldEventsSubsystem.h"

EBTNodeResult::Type UBTT_DestroyEntity::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const ABaseController* BaseController{Cast<ABaseController>(OwnerComp.GetAIOwner())}; BaseController != nullptr)
	{
		if (APawn* Pawn{BaseController->GetPawn()}; Pawn != nullptr)
		{
			// Destroy pawn from world and broadcast event
			Pawn->Destroy();
			GetWorld()->GetSubsystem<UWorldEventsSubsystem>()->OnEntityDeath.Broadcast();
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Aborted;
}
