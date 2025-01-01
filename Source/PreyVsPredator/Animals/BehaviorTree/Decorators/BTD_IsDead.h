#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTD_IsDead.generated.h"


UCLASS()
class PREYVSPREDATOR_API UBTD_IsDead : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Blackboard In")
	FBlackboardKeySelector DeadKey;

public:
	UBTD_IsDead();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
