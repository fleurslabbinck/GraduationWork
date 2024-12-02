#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"
#include "GrazingState.generated.h"

class APreyController;

UCLASS()
class PREYVSPREDATOR_API UGrazingState : public UStateBase
{
	GENERATED_BODY()

public:
	UGrazingState() = default;
	
	virtual void OnEnter(APreyController* AIOwner, UBlackboardComponent* BlackboardComponent) override;
	virtual void OnExit(APreyController* AIOwner, UBlackboardComponent* BlackboardComponent) override;
};
