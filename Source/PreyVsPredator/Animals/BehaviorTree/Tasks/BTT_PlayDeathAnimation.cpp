#include "BTT_PlayDeathAnimation.h"

#include "PreyVsPredator/Animals/BaseAnimal/BaseController.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"


EBTNodeResult::Type UBTT_PlayDeathAnimation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const ABaseController* BaseController{Cast<ABaseController>(OwnerComp.GetAIOwner())}; BaseController != nullptr)
	{
		if (const ABaseEntity* Entity{Cast<ABaseEntity>(BaseController->GetPawn())}; Entity != nullptr)
		{
			// Broadcast death event to start death animation
			Entity->OnDeath.Broadcast();
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Aborted;
}
