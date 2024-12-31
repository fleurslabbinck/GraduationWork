#include "BTD_Thirsty.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"

UBTD_Thirsty::UBTD_Thirsty()
{
	ThirstyKey.AddBoolFilter(this, "Thirsty");
}

bool UBTD_Thirsty::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool Thirsty{false};

	if (const AAIController* Controller{Cast<AAIController>(OwnerComp.GetAIOwner())}; Controller != nullptr)
	{
		if (const ABaseEntity* Entity{Cast<ABaseEntity>(Controller->GetPawn())}; Entity != nullptr)
		{
			// Thirsty if blackboard thirsty key is true and if not already full water
			Thirsty = OwnerComp.GetBlackboardComponent()->GetValueAsBool(ThirstyKey.SelectedKeyName) && !Entity->FullWater();
		}
	}

	return Thirsty;
}
