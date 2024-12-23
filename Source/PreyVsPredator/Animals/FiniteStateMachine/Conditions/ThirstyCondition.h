#pragma once

#include "CoreMinimal.h"
#include "ConditionBase.h"
#include "ThirstyCondition.generated.h"


UCLASS()
class PREYVSPREDATOR_API UThirstyCondition : public UConditionBase
{
	GENERATED_BODY()

public:
	UThirstyCondition() = default;

	virtual bool Evaluate(UBlackboardComponent* BlackboardComponent) const override;
};
