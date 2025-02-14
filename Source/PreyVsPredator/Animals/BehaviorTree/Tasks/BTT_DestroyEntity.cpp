﻿#include "BTT_DestroyEntity.h"

#include "AIController.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"
#include "PreyVsPredator/Animals/Flocking/BaseFlock.h"
#include "PreyVsPredator/Animals/WorldEvents/WorldEventsSubsystem.h"

EBTNodeResult::Type UBTT_DestroyEntity::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const AAIController* Controller{Cast<AAIController>(OwnerComp.GetAIOwner())}; Controller != nullptr)
	{
		if (ABaseEntity* Entity{Cast<ABaseEntity>(Controller->GetPawn())}; Entity != nullptr)
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
