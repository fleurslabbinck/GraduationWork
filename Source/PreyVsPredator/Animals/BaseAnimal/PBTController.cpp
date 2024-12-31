#include "PBTController.h"


void APBTController::BeginPlay()
{
	Super::BeginPlay();

	// Start to run behavior tree
	checkf(BehaviorTree != nullptr, TEXT("Behavior Tree not assigned"))
	if (!RunBehaviorTree(BehaviorTree))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, TEXT("NO"));
	}
}
