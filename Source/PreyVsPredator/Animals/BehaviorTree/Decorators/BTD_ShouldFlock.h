#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTD_ShouldFlock.generated.h"


UCLASS()
class PREYVSPREDATOR_API UBTD_ShouldFlock : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector ShouldFlockKey;

	UPROPERTY(EditAnywhere, Category="Blackboard Out")
	FBlackboardKeySelector ReachedDestinationKey;

public:
	UBTD_ShouldFlock();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
