#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"
#include "GrazingState.generated.h"


UCLASS()
class PREYVSPREDATOR_API UGrazingState : public UStateBase
{
	GENERATED_BODY()

public:
	UGrazingState();
	
	virtual void OnEnter(UBlackboardComponent* BlackboardComponent) override;
	virtual void OnExit(UBlackboardComponent* BlackboardComponent) override;

private:
	float m_MaxGrazingSpeed{100.f};
};
