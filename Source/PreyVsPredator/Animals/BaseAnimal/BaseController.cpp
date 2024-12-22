#include "BaseController.h"

#include "PreyVsPredator/Animals/FiniteStateMachine/FiniteStateMachine.h"
#include "PreyVsPredator/Animals/FiniteStateMachine/Conditions/ToFlockingState.h"
#include "PreyVsPredator/Animals/FiniteStateMachine/States/FlockingState.h"
#include "PreyVsPredator/Animals/FiniteStateMachine/States/GrazingState.h"


ABaseController::ABaseController()
{
	PrimaryActorTick.bCanEverTick = false;
	
	FiniteStateMachine = CreateDefaultSubobject<UFiniteStateMachine>("Finite State Machine");

	// Create states
	m_GrazingState = NewObject<UGrazingState>();
	m_FlockingState = NewObject<UFlockingState>();

	// Create conditions
	m_ToFlockingState = NewObject<UToFlockingState>();
}

void ABaseController::BeginPlay()
{
	Super::BeginPlay();

	// Set Behavior Tree classes
	m_GrazingState->InitializeState(this, GrazingBehaviorTree);
	m_FlockingState->InitializeState(this, FlockingBehaviorTree);

	// Create transitions
	FiniteStateMachine->SetStartState(m_GrazingState);
	FiniteStateMachine->AddTransition(m_GrazingState, m_FlockingState, m_ToFlockingState);
}

void ABaseController::SetTimer(const FTimerDelegate& Delegate, float InRate)
{
	GetWorld()->GetTimerManager().SetTimer(m_Timer, Delegate, InRate, false);
}

void ABaseController::ResetTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(m_Timer);
}