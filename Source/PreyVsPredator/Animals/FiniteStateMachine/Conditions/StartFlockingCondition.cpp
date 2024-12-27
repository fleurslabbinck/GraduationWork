#include "StartFlockingCondition.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"

FName UStartFlockingCondition::FlockLocationName{"FlockLocation"};

bool UStartFlockingCondition::Evaluate(UBlackboardComponent* BlackboardComponent) const
{
	bool ShouldFlock{false};
	
	if (const AAIController* Controller{Cast<AAIController>(BlackboardComponent->GetOwner())}; Controller != nullptr)
	{
		if (ABaseEntity* Entity{Cast<ABaseEntity>(Controller->GetPawn())}; Entity != nullptr)
		{
			ShouldFlock = Entity->ShouldFlock();
			if (ShouldFlock)
			{
				// Set the flock location entity should go to in blackboard
				const FVector FlockLocation{};
				BlackboardComponent->SetValueAsVector(FlockLocationName, FlockLocation);
				
				// Only reset if entity should flock
				Entity->ResetFlockTimer();
			}
		}
	}
	
	return ShouldFlock;
}
