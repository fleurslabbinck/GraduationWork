#include "FullWaterCondition.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"


bool UFullWaterCondition::Evaluate(UBlackboardComponent* BlackboardComponent) const
{
	bool FullWater{false};
	
	if (const AAIController* Controller{Cast<AAIController>(BlackboardComponent->GetOwner())}; Controller != nullptr)
	{
		if (const ABaseEntity* Entity{Cast<ABaseEntity>(Controller->GetPawn())}; Entity != nullptr)
		{
			// Check if entity has full water
			FullWater = Entity->FullWater();
		}
	}
	
	return FullWater;
}
