#pragma once

#include "CoreMinimal.h"
#include "ConditionBase.h"
#include "StartFlockingCondition.generated.h"


UCLASS()
class PREYVSPREDATOR_API UStartFlockingCondition : public UConditionBase
{
	GENERATED_BODY()

public:
	UStartFlockingCondition() = default;
	
	virtual bool Evaluate(UBlackboardComponent* BlackboardComponent) const override;
};
