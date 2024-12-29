#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatsBar.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProgressChanged, float, NewValue);

class UProgressBar;

UCLASS()
class PREYVSPREDATOR_API UStatsBar : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget, AllowPrivateAccess = "true"))
	UProgressBar* StatBar;

public:
	FOnProgressChanged OnProgressChanged;

protected:
	virtual void NativeConstruct() override;

private:
	const float m_MaxValue{100.f};
	
	UFUNCTION()
	void UpdateProgress(float NewValue);
};
