#include "BTT_EatGrass.h"

#include "AIController.h"
#include "PreyVsPredator/Animals/Prey/PreyController.h"
#include "PreyVsPredator/InfluenceMaps/WorldGridSubsystem.h"


UBTT_EatGrass::UBTT_EatGrass()
{
	bNotifyTick = false;
}

EBTNodeResult::Type UBTT_EatGrass::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EatGrass(&OwnerComp);
	
	return EBTNodeResult::InProgress;
}

void UBTT_EatGrass::EatGrass(UBehaviorTreeComponent* OwnerComp)
{
	APreyController* PreyController{Cast<APreyController>(OwnerComp->GetAIOwner())};
	if (PreyController == nullptr) return FinishLatentAbort(*OwnerComp);
	
	// Try to eat grass
	const FVector CurrentPosition{PreyController->GetPawn()->GetActorLocation()};
	if (GetWorld()->GetSubsystem<UWorldGridSubsystem>()->AttemptConsumption(CurrentPosition, m_GrassType))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("Consuming Grass"));
		PreyController->SetTimer(FTimerDelegate::CreateUObject(this, &UBTT_EatGrass::EatGrass, OwnerComp), EatTime);
	}
	else
	{
		// Succeed if grass not eaten
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("Grass eaten"));
		FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
	}
}