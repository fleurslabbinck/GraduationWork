#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"
#include "FlockingState.generated.h"

class APreyController;

UCLASS()
class PREYVSPREDATOR_API UFlockingState : public UStateBase
{
	GENERATED_BODY()

public:
	UFlockingState() = default;
	
	virtual void OnEnter(APreyController* AIOwner, UBlackboardComponent* BlackboardComponent) override;
	virtual void Update(APreyController* AIOwner, UBlackboardComponent* BlackboardComponent, float DeltaTime) override;
	virtual void OnExit(APreyController* AIOwner, UBlackboardComponent* BlackboardComponent) override;
};
