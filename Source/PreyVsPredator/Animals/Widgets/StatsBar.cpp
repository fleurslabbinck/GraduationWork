#include "StatsBar.h"

#include "Components/ProgressBar.h"

void UStatsBar::NativeConstruct()
{
	Super::NativeConstruct();

	OnProgressChanged.AddDynamic(this, &UStatsBar::UpdateProgress);
}

void UStatsBar::UpdateProgress(float NewValue)
{
	StatBar->SetPercent(NewValue / m_MaxValue);
}
