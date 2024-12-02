#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ConditionBase.generated.h"


class UBlackboardComponent;

UCLASS()
class PREYVSPREDATOR_API UConditionBase : public UObject
{
	GENERATED_BODY()

public:
	UConditionBase() = default;

	virtual bool Evaluate(UBlackboardComponent* BlackboardComponent) const
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red,TEXT("Warning: virtual bool Evaluate(UBlackboardComponent* BlackboardComponent) const not overriden!"));
		return false;
	}
};
