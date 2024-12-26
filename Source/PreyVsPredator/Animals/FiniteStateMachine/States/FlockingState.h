#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"
#include "FlockingState.generated.h"


UCLASS()
class PREYVSPREDATOR_API UFlockingState : public UStateBase
{
	GENERATED_BODY()

public:
	UFlockingState() = default;
	
	virtual void InitializeState(AAIController* AIController, UBehaviorTree* BehaviorTree) override;
	
	virtual void OnEnter(UBlackboardComponent* BlackboardComponent) override;

private:
	FName m_ReachedDestinationKeyName{};
};
