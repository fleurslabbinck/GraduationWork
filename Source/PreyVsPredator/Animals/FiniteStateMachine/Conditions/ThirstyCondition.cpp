#include "ThirstyCondition.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"
#include "PreyVsPredator/Animals/Flocking/BaseFlock.h"


bool UThirstyCondition::Evaluate(UBlackboardComponent* BlackboardComponent) const
{
	bool Thirsty{false};
	
	if (const AAIController* Controller{Cast<AAIController>(BlackboardComponent->GetOwner())}; Controller != nullptr)
	{
		if (const ABaseEntity* Entity{Cast<ABaseEntity>(Controller->GetPawn())}; Entity != nullptr)
		{
			if (ABaseFlock* Flock{Entity->Flock()}; Flock != nullptr)
			{
				// Check if flock is thirsty and no entity is hungry
				Thirsty = Flock->Thirsty() && !Flock->Hungry();
			}
			else
			{
				Thirsty = Entity->Thirsty();
			}
		}
	}
	
	return Thirsty;
}
