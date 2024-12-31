#include "PBTController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"


APBTController::APBTController()
{
	PrimaryActorTick.bCanEverTick = false;

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("Behavior Tree Component");
}

void APBTController::BeginPlay()
{
	Super::BeginPlay();

	// Start to run behavior tree
	RunBehaviorTree(BehaviorTreeComponent->GetRootTree());
}
