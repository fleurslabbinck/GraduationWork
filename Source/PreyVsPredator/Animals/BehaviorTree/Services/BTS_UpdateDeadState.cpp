#include "BTS_UpdateDeadState.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"

UBTS_UpdateDeadState::UBTS_UpdateDeadState()
{
	DeadKey.AddBoolFilter(this, "Dead");
}

void UBTS_UpdateDeadState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (const AAIController* Controller{Cast<AAIController>(OwnerComp.GetAIOwner())}; Controller != nullptr)
	{
		if (const ABaseEntity* Entity{Cast<ABaseEntity>(Controller->GetPawn())}; Entity != nullptr)
		{
			// Check if entity is dead
			if (Entity->Dead())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(DeadKey.SelectedKeyName, true);

				// Restart tree so entity can die
				OwnerComp.RestartTree();
			}
		}
	}
}
