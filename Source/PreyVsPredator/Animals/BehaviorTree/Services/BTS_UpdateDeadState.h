#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_UpdateDeadState.generated.h"


UCLASS()
class PREYVSPREDATOR_API UBTS_UpdateDeadState : public UBTService
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="Blackboard Out")
	FBlackboardKeySelector DeadKey;

public:
	UBTS_UpdateDeadState();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
