#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"
#include "DrinkingState.generated.h"


UCLASS()
class PREYVSPREDATOR_API UDrinkingState : public UStateBase
{
	GENERATED_BODY()

public:
	UDrinkingState();

	virtual void OnEnter(UBlackboardComponent* BlackboardComponent) override;
	virtual void OnExit(UBlackboardComponent* BlackboardComponent) override;

private:
	float m_MaxDrinkingSpeed{300.f};
};
