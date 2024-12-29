#include "ThirstyCondition.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"
#include "PreyVsPredator/Animals/Flocking/BaseFlock.h"


bool UThirstyCondition::Evaluate(UBlackboardComponent* BlackboardComponent) const
{
	bool ShouldHydrate{false};
	
	if (const AAIController* Controller{Cast<AAIController>(BlackboardComponent->GetOwner())}; Controller != nullptr)
	{
		if (const ABaseEntity* Entity{Cast<ABaseEntity>(Controller->GetPawn())}; Entity != nullptr)
		{
			if (const ABaseFlock* Flock{Entity->Flock()}; Flock != nullptr)
			{
				ShouldHydrate = Flock->Thirsty();
			}
			else
			{
				ShouldHydrate = Entity->Thirsty();
			}
		}
	}
	
	return ShouldHydrate;
}
