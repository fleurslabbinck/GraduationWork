#pragma once

#include "CoreMinimal.h"
#include "ConditionBase.h"
#include "TestCondition.generated.h"


UCLASS()
class PREYVSPREDATOR_API UTestCondition : public UConditionBase
{
	GENERATED_BODY()

public:
	virtual bool Evaluate(UBlackboardComponent* BlackboardComponent) const override;
};
