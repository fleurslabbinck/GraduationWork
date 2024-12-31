#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_UpdateShouldFlock.generated.h"


UCLASS()
class PREYVSPREDATOR_API UBTS_UpdateShouldFlock : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Blackboard Out")
	FBlackboardKeySelector ShouldFlockKey;

	UPROPERTY(EditAnywhere, Category="Blackboard Out")
	FBlackboardKeySelector FlockLocationKey;

public:
	UBTS_UpdateShouldFlock();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
