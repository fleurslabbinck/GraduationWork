#pragma once

#include "CoreMinimal.h"
#include "ConditionBase.h"
#include "ToFlockingState.generated.h"


UCLASS()
class PREYVSPREDATOR_API UToFlockingState : public UConditionBase
{
	GENERATED_BODY()

public:
	UToFlockingState() = default;
	
	virtual bool Evaluate(UBlackboardComponent* BlackboardComponent) const override;
};
