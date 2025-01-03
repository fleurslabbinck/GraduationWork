#include "BTT_PlayDeathAnimation.h"

#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"


EBTNodeResult::Type UBTT_PlayDeathAnimation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const AAIController* Controller{Cast<AAIController>(OwnerComp.GetAIOwner())}; Controller != nullptr)
	{
		if (const ABaseEntity* Entity{Cast<ABaseEntity>(Controller->GetPawn())}; Entity != nullptr)
		{
			// Broadcast death event to start death animation
			Entity->OnDeath.Broadcast();

			// Stop movement
			Entity->GetCharacterMovement()->StopActiveMovement();
			
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Aborted;
}
