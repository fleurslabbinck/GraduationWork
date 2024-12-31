#include "BTS_UpdateShouldFlock.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseController.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"
#include "PreyVsPredator/Animals/Flocking/BaseFlock.h"

UBTS_UpdateShouldFlock::UBTS_UpdateShouldFlock()
{
	ShouldFlockKey.AddBoolFilter(this, "ShouldFlock");
	FlockLocationKey.AddVectorFilter(this, "FlockLocation");
}

void UBTS_UpdateShouldFlock::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (const AAIController* Controller{Cast<AAIController>(OwnerComp.GetAIOwner())}; Controller != nullptr)
	{
		if (ABaseEntity* Entity{Cast<ABaseEntity>(Controller->GetPawn())}; Entity != nullptr)
		{
			if (const bool ShouldFlock{Entity->ShouldFlock()})
			{
				UBlackboardComponent* BlackboardComponent{OwnerComp.GetBlackboardComponent()};

				// Set the flock location entity should go to in blackboard
				const FVector FlockLocation{Entity->Flock()->FlockLocation()};
				BlackboardComponent->SetValueAsVector(FlockLocationKey.SelectedKeyName, FlockLocation);
				
				// Only reset if entity should flock
				Entity->ResetFlockTimer();

				// Set should flock in blackboard
				BlackboardComponent->SetValueAsBool(ShouldFlockKey.SelectedKeyName, ShouldFlock);
			}
		}
	}
}
