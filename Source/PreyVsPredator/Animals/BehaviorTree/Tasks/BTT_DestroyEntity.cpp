#include "BTT_DestroyEntity.h"

#include "PreyVsPredator/Animals/BaseAnimal/BaseController.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"
#include "PreyVsPredator/Animals/Flocking/BaseFlock.h"
#include "PreyVsPredator/Animals/Subsystems/WorldEventsSubsystem.h"

EBTNodeResult::Type UBTT_DestroyEntity::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const ABaseController* BaseController{Cast<ABaseController>(OwnerComp.GetAIOwner())}; BaseController != nullptr)
	{
		if (ABaseEntity* Entity{Cast<ABaseEntity>(BaseController->GetPawn())}; Entity != nullptr)
		{
			if (ABaseFlock* Flock{Entity->Flock()}; Flock != nullptr)
			{
				// If entity was in flock, remove from flock
				Flock->RemoveEntity(Entity);
			}
			
			// Destroy entity from world and broadcast event
			Entity->Destroy();
			GetWorld()->GetSubsystem<UWorldEventsSubsystem>()->OnEntityDeath.Broadcast();
			
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Aborted;
}
