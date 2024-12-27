#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"
#include "DrinkingState.generated.h"


UCLASS()
class PREYVSPREDATOR_API UDrinkingState : public UStateBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Hydrating")
	float HydratingSpeed{300.f};

public:
	UDrinkingState() = default;

	virtual void OnEnter(UBlackboardComponent* BlackboardComponent) override;
	virtual void OnExit(UBlackboardComponent* BlackboardComponent) override;

protected:
	virtual void UpdateMaxSpeed() override;
};
