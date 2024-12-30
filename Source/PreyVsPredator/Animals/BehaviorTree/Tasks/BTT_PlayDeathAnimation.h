#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_PlayDeathAnimation.generated.h"


UCLASS()
class PREYVSPREDATOR_API UBTT_PlayDeathAnimation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTT_PlayDeathAnimation() = default;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
