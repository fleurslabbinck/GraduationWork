#include "BTT_EatGrass.h"

#include "AIController.h"
#include "PreyVsPredator/InfluenceMaps/WorldGridSubsystem.h"

class UWorldGridSubsystem;

UBTT_EatGrass::UBTT_EatGrass()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTT_EatGrass::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EatGrass(&OwnerComp);
	
	return EBTNodeResult::InProgress;
}

void UBTT_EatGrass::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	
}

void UBTT_EatGrass::EatGrass(UBehaviorTreeComponent* OwnerComp)
{
	AAIController* Controller{OwnerComp->GetAIOwner()};
	if (Controller == nullptr) return FinishLatentAbort(*OwnerComp);
	
	// Get current grass patch from world grid
	const FVector CurrentPosition{Controller->GetPawn()->GetActorLocation()};
	UGridCell* GridCell{GetWorld()->GetSubsystem<UWorldGridSubsystem>()->NextGrassPatch(CurrentPosition)};
	
	UWorldGridCell* GrassPatch{Cast<UWorldGridCell>(GridCell)};
	if (GridCell == nullptr) FinishLatentAbort(*OwnerComp);
	
	if (GrassPatch->Consume())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("Consuming Grass"));
		GetWorld()->GetTimerManager().SetTimer(m_EatTimer, FTimerDelegate::CreateUObject(this, &UBTT_EatGrass::EatGrass, OwnerComp), EatTime, false);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("Grass eaten"));
		FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
	}
}