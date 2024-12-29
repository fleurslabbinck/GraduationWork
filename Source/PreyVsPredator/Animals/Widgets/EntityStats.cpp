#include "EntityStats.h"

#include "StatsBar.h"


void UEntityStats::UpdateStatsBar(EStatsBarType Type, float NewValue) const
{
	switch (Type)
	{
	case EStatsBarType::Stamina:
		StaminaBar->OnProgressChanged.Broadcast(NewValue);
		break;
	case EStatsBarType::Health:
		HealthBar->OnProgressChanged.Broadcast(NewValue);
		break;
	case EStatsBarType::Hunger:
		HungerBar->OnProgressChanged.Broadcast(NewValue);
		break;
	case EStatsBarType::Thirst:
		ThirstBar->OnProgressChanged.Broadcast(NewValue);
		break;
	}
}
