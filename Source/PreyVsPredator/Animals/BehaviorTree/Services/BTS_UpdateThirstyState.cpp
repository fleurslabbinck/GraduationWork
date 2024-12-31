#include "BTS_UpdateThirstyState.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseController.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"
#include "PreyVsPredator/Animals/Flocking/BaseFlock.h"

UBTS_UpdateThirstyState::UBTS_UpdateThirstyState()
{
	ThirstyKey.AddBoolFilter(this, "Thirsty");
}

void UBTS_UpdateThirstyState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (const AAIController* Controller{Cast<AAIController>(OwnerComp.GetAIOwner())}; Controller != nullptr)
	{
		if (ABaseEntity* Entity{Cast<ABaseEntity>(Controller->GetPawn())}; Entity != nullptr)
		{
			bool Thirsty{false};
			
			if (const ABaseFlock* Flock{Entity->Flock()}; Flock != nullptr)
			{
				// Check if flock is thirsty and no entity is hungry
				Thirsty = Flock->Thirsty() && !Flock->Hungry();
			}
			else
			{
				Thirsty = Entity->Thirsty();
			}

			OwnerComp.GetBlackboardComponent()->SetValueAsBool(ThirstyKey.SelectedKeyName, Thirsty);
		}
	}
}
