#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_SetMaxSpeed.generated.h"


UCLASS()
class PREYVSPREDATOR_API UBTT_SetMaxSpeed : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Params")
	float MaxSpeed{800.f};

public:
	UBTT_SetMaxSpeed() = default;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
