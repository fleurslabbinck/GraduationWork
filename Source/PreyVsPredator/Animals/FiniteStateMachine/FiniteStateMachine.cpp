#include "FiniteStateMachine.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Conditions/ConditionBase.h"
#include "States/StateBase.h"


UFiniteStateMachine::UFiniteStateMachine()
{
	PrimaryComponentTick.bCanEverTick = true;

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>("Blackboard Component");
}

void UFiniteStateMachine::BeginPlay()
{
	Super::BeginPlay();

	checkf(BlackboardComponent != nullptr, TEXT("Blackboard not assigned"));
}

void UFiniteStateMachine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Transitions.Contains(m_CurrentState))
	{
		// Get transition array
		const auto* TransitionArray{Transitions.Find(m_CurrentState)};

		// Loop over transition array
		for (const FTransitionStatePair& TransitionStatePair : *TransitionArray)
		{
			// Evaluate condition
			const UConditionBase* Condition{TransitionStatePair.Key};
			if (Condition != nullptr && Condition->Evaluate(BlackboardComponent))
			{
				// Transition to state if condition is met
				UStateBase* ToState{TransitionStatePair.Value};
				ChangeState(ToState);
				break;
			}
		}
	}
	
	// Update current state
	if (m_CurrentState != nullptr)
	{
		m_CurrentState->Update(BlackboardComponent, DeltaTime);
	}
}

void UFiniteStateMachine::SetStartState(UStateBase* StartState)
{
	ChangeState(StartState);
}

void UFiniteStateMachine::AddTransition(UStateBase* StartState, UStateBase* ToState, UConditionBase* Condition)
{
	// Check if StartState exists
	if (!Transitions.Contains(StartState))
	{
		// Add start state
		Transitions.Add(StartState, FTransitions());
	}
	if (Transitions.Contains(StartState))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("Added Start State"));
	}

	// Add transition from start state to end state
	Transitions[StartState].Add(FTransitionStatePair(Condition, ToState));
}

UBlackboardComponent* UFiniteStateMachine::GetBlackboard() const
{
	return BlackboardComponent;
}

void UFiniteStateMachine::ChangeState(UStateBase* NewState)
{
	// Execute OnExit if currently in state
	if (m_CurrentState != nullptr)
	{
		m_CurrentState->OnExit(BlackboardComponent);
	}

	// Change current state
	m_CurrentState = NewState;

	// Execute OnEnter of new state
	if (m_CurrentState != nullptr)
	{
		m_CurrentState->OnEnter(BlackboardComponent);
	}
}