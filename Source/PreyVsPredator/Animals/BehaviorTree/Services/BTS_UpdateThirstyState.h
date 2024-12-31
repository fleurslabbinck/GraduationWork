#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_UpdateThirstyState.generated.h"


UCLASS()
class PREYVSPREDATOR_API UBTS_UpdateThirstyState : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Blackboard Out")
	FBlackboardKeySelector ThirstyKey;

public:
	UBTS_UpdateThirstyState();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
