#include "BTT_DestroyEntity.h"

#include "PreyVsPredator/Animals/BaseAnimal/BaseController.h"

EBTNodeResult::Type UBTT_DestroyEntity::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const ABaseController* BaseController{Cast<ABaseController>(OwnerComp.GetAIOwner())}; BaseController != nullptr)
	{
		if (APawn* Pawn{BaseController->GetPawn()}; Pawn != nullptr)
		{
			// Destroy pawn from world
			Pawn->Destroy();
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Aborted;
}
