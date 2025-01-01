#include "BTT_SetMaxSpeed.h"

#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"

EBTNodeResult::Type UBTT_SetMaxSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const AAIController* Controller{Cast<AAIController>(OwnerComp.GetAIOwner())}; Controller != nullptr)
	{
		if (ABaseEntity* Entity{Cast<ABaseEntity>(Controller->GetPawn())}; Entity != nullptr)
		{
			UCharacterMovementComponent* Movement{Entity->GetCharacterMovement()};
			Movement->MaxWalkSpeed = Entity->SpeedFactor() * MaxSpeed;

			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Aborted;
}
