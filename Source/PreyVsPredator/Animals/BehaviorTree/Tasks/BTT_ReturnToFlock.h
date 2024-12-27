#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_ReturnToFlock.generated.h"

UCLASS()
class PREYVSPREDATOR_API UBTT_ReturnToFlock : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Blackboard In")
	FBlackboardKeySelector FlockLocationKey;

	UPROPERTY(EditAnywhere, Category="Blackboard Out")
	FBlackboardKeySelector ReachedDestinationKey;

public:
	UBTT_ReturnToFlock();

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
