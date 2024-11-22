#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FiniteStateMachine.generated.h"

class UConditionBase;
class UBlackboardComponent;
class UStateBase;

UCLASS()
class PREYVSPREDATOR_API UFiniteStateMachine final : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Instanced, Category = "AI")
	UBlackboardComponent* BlackboardComponent;

public:
	UFiniteStateMachine();

	void SetStartState(UStateBase* StartState);
	void AddTransition(UStateBase* StartState, UStateBase* ToState, UConditionBase* Condition);
	UBlackboardComponent* GetBlackboard() const;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	UStateBase* m_CurrentState{};
	
	typedef TTuple<UConditionBase*, UStateBase*> FTransitionStatePair;
	typedef TArray<FTransitionStatePair> FTransitions;

	TMap<UStateBase*, FTransitions> Transitions;

	void ChangeState(UStateBase* NewState);
};
