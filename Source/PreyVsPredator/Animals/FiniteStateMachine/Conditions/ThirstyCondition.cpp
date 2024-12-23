#include "ThirstyCondition.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"


bool UThirstyCondition::Evaluate(UBlackboardComponent* BlackboardComponent) const
{
	bool ShouldHydrate{false};
	
	if (const AAIController* Controller{Cast<AAIController>(BlackboardComponent->GetOwner())}; Controller != nullptr)
	{
		if (const ABaseEntity* Entity{Cast<ABaseEntity>(Controller->GetPawn())}; Entity != nullptr)
		{
			ShouldHydrate = Entity->Thirsty();
		}
	}
	
	return ShouldHydrate;
}
