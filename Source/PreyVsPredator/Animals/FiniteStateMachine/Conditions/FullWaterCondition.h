#pragma once

#include "CoreMinimal.h"
#include "ConditionBase.h"
#include "FullWaterCondition.generated.h"


UCLASS()
class PREYVSPREDATOR_API UFullWaterCondition : public UConditionBase
{
	GENERATED_BODY()

public:
	UFullWaterCondition() = default;

	virtual bool Evaluate(UBlackboardComponent* BlackboardComponent) const override;
};
