#pragma once

#include "CoreMinimal.h"
#include "ConditionBase.h"
#include "StopFlockingCondition.generated.h"


UCLASS()
class PREYVSPREDATOR_API UStopFlockingCondition : public UConditionBase
{
	GENERATED_BODY()

public:
	UStopFlockingCondition() = default;
	
	virtual bool Evaluate(UBlackboardComponent* BlackboardComponent) const override;

private:
	static FName ReachedDestinationName;
};
