#include "BTD_NotThirsty.h"

#include "PreyVsPredator/Animals/BaseAnimal/BaseController.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"

bool UBTD_NotThirsty::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool Thirsty{false};

	if (const AAIController* Controller{Cast<AAIController>(OwnerComp.GetAIOwner())}; Controller != nullptr)
	{
		if (const ABaseEntity* Entity{Cast<ABaseEntity>(Controller->GetPawn())}; Entity != nullptr)
		{
			Thirsty = Entity->Thirsty();
		}
	}

	// Return not thirsty
	return !Thirsty;
}
