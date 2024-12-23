#pragma once

#include "CoreMinimal.h"
#include "ConditionBase.h"
#include "FlockOutOfReachCondition.generated.h"


UCLASS()
class PREYVSPREDATOR_API UFlockOutOfReachCondition : public UConditionBase
{
	GENERATED_BODY()

public:
	UFlockOutOfReachCondition() = default;
	
	virtual bool Evaluate(UBlackboardComponent* BlackboardComponent) const override;
};
