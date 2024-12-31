#pragma once

#include "CoreMinimal.h"
#include "SimulationData.generated.h"

UENUM(BlueprintType)
enum class ESimulationMethod : uint8
{
	HFSMBTH UMETA(DisplayName="HierarchicalFiniteStateMachineBehaviorTreeHybrid"),
	PBT UMETA(DisplayName="PureBehaviorTree")
};