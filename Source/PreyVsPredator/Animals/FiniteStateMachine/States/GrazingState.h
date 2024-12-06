#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"
#include "GrazingState.generated.h"


UCLASS()
class PREYVSPREDATOR_API UGrazingState : public UStateBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Grazing")
	float GrazingSpeed{100.f};

public:
	UGrazingState() = default;
	
	virtual void OnEnter(UBlackboardComponent* BlackboardComponent) override;
	virtual void OnExit(UBlackboardComponent* BlackboardComponent) override;

protected:
	virtual void UpdateMaxSpeed() override;
};
