#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_NotThirsty.generated.h"


UCLASS()
class PREYVSPREDATOR_API UBTD_NotThirsty : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTD_NotThirsty() = default;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
