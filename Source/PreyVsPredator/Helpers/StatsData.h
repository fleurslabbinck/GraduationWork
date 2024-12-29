#pragma once

#include "CoreMinimal.h"
#include "StatsData.generated.h"

UENUM(BlueprintType)
enum class EStatsBarType : uint8
{
	Stamina UMETA(DisplayName="STAMINA"),
	Health UMETA(DisplayName="HEALTH"),
	Hunger UMETA(DisplayName="HUNGER"),
	Thirst UMETA(DisplayName="THIRST")
};