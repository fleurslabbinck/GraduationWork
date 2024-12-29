#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PreyVsPredator/Helpers/StatsData.h"
#include "EntityStats.generated.h"


class UStatsBar;

UCLASS()
class PREYVSPREDATOR_API UEntityStats : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget, AllowPrivateAccess = "true"))
	UStatsBar* StaminaBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget, AllowPrivateAccess = "true"))
	UStatsBar* HealthBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget, AllowPrivateAccess = "true"))
	UStatsBar* HungerBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget, AllowPrivateAccess = "true"))
	UStatsBar* ThirstBar;

public:
	void UpdateStatsBar(EStatsBarType Type ,float NewValue) const;
};
