#include "DeadCondition.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"

bool UDeadCondition::Evaluate(UBlackboardComponent* BlackboardComponent) const
{
	bool Dead{false};
	
	if (const AAIController* Controller{Cast<AAIController>(BlackboardComponent->GetOwner())}; Controller != nullptr)
	{
		if (const ABaseEntity* Entity{Cast<ABaseEntity>(Controller->GetPawn())}; Entity != nullptr)
		{
			// Check if entity is dead
			Dead = Entity->Dead();
		}
	}
	
	return Dead;
}
