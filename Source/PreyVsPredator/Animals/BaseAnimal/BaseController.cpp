#include "BaseController.h"

#include "PreyVsPredator/Animals/FiniteStateMachine/FiniteStateMachine.h"
#include "PreyVsPredator/Animals/FiniteStateMachine/Conditions/StartFlockingCondition.h"
#include "PreyVsPredator/Animals/FiniteStateMachine/Conditions/StopFlockingCondition.h"
#include "PreyVsPredator/Animals/FiniteStateMachine/Conditions/ThirstyCondition.h"
#include "PreyVsPredator/Animals/FiniteStateMachine/States/FlockingState.h"
#include "PreyVsPredator/Animals/FiniteStateMachine/States/GrazingState.h"
#include "PreyVsPredator/Animals/FiniteStateMachine/States/DrinkingState.h"


ABaseController::ABaseController()
{
	PrimaryActorTick.bCanEverTick = false;
	
	FiniteStateMachine = CreateDefaultSubobject<UFiniteStateMachine>("Finite State Machine");
}

void ABaseController::BeginPlay()
{
	Super::BeginPlay();

	// Create states
	m_GrazingState = NewObject<UGrazingState>(GetWorld());
	m_DrinkingState = NewObject<UDrinkingState>(GetWorld());
	m_FlockingState = NewObject<UFlockingState>(GetWorld());

	// Create conditions
	m_ThirstyCondition = NewObject<UThirstyCondition>();
	m_StartFlockingCondition = NewObject<UStartFlockingCondition>();
	m_StopFlockingCondition = NewObject<UStopFlockingCondition>();

	// Set Behavior Tree classes
	m_GrazingState->InitializeState(this, GrazingBehaviorTree);
	m_DrinkingState->InitializeState(this, DrinkingBehaviorTree);
	m_FlockingState->InitializeState(this, FlockingBehaviorTree);

	// Create transitions
	FiniteStateMachine->SetStartState(m_GrazingState);
	FiniteStateMachine->AddTransition(m_GrazingState, m_DrinkingState, m_ThirstyCondition);
	FiniteStateMachine->AddTransition(m_FlockingState, m_DrinkingState, m_ThirstyCondition);
	FiniteStateMachine->AddTransition(m_GrazingState, m_FlockingState, m_StartFlockingCondition);
	FiniteStateMachine->AddTransition(m_FlockingState, m_GrazingState, m_StopFlockingCondition);
}

void ABaseController::SetTimer(const FTimerDelegate& Delegate, float InRate)
{
	GetWorld()->GetTimerManager().SetTimer(m_Timer, Delegate, InRate, false);
}

void ABaseController::ResetTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(m_Timer);
}
