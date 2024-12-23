#include "FlockOutOfReachCondition.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"


bool UFlockOutOfReachCondition::Evaluate(UBlackboardComponent* BlackboardComponent) const
{
	bool ShouldFlock{false};
	
	if (const AAIController* Controller{Cast<AAIController>(BlackboardComponent->GetOwner())}; Controller != nullptr)
	{
		if (ABaseEntity* Entity{Cast<ABaseEntity>(Controller->GetPawn())}; Entity != nullptr)
		{
			ShouldFlock = Entity->ShouldFlock();
			if (ShouldFlock)
			{
				// Only reset if entity should flock
				Entity->ResetFlockTimer();
			}
		}
	}
	
	return ShouldFlock;
}
