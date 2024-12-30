#pragma once

#include "CoreMinimal.h"
#include "ConditionBase.h"
#include "DeadCondition.generated.h"


UCLASS()
class PREYVSPREDATOR_API UDeadCondition : public UConditionBase
{
	GENERATED_BODY()

public:
	UDeadCondition() = default;

	virtual bool Evaluate(UBlackboardComponent* BlackboardComponent) const override;
};
