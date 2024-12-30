#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"
#include "DyingState.generated.h"


UCLASS()
class PREYVSPREDATOR_API UDyingState : public UStateBase
{
	GENERATED_BODY()

public:
	UDyingState() = default;

	virtual void OnEnter(UBlackboardComponent* BlackboardComponent) override;
};
