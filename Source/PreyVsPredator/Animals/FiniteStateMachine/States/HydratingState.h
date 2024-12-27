#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"
#include "HydratingState.generated.h"


UCLASS()
class PREYVSPREDATOR_API UHydratingState : public UStateBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Hydrating")
	float HydratingSpeed{300.f};

public:
	UHydratingState() = default;

	virtual void OnEnter(UBlackboardComponent* BlackboardComponent) override;
	virtual void OnExit(UBlackboardComponent* BlackboardComponent) override;

protected:
	virtual void UpdateMaxSpeed() override;
};
