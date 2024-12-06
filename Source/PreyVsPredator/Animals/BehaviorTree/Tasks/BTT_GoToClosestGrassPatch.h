#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_GoToClosestGrassPatch.generated.h"


UCLASS()
class PREYVSPREDATOR_API UBTT_GoToClosestGrassPatch : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTT_GoToClosestGrassPatch();

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
