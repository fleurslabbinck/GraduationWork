#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTD_Thirsty.generated.h"


UCLASS()
class PREYVSPREDATOR_API UBTD_Thirsty : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Blackboard In")
	FBlackboardKeySelector ThirstyKey;

public:
	UBTD_Thirsty();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
