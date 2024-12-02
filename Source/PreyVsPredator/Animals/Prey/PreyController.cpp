#include "PreyController.h"

#include "PreyVsPredator/Animals/FiniteStateMachine/FiniteStateMachine.h"
#include "PreyVsPredator/Animals/FiniteStateMachine/Conditions/TestCondition.h"
#include "PreyVsPredator/Animals/FiniteStateMachine/States/FlockingState.h"
#include "PreyVsPredator/Animals/FiniteStateMachine/States/GrazingState.h"


APreyController::APreyController()
{
	PrimaryActorTick.bCanEverTick = false;
	
	FiniteStateMachine = CreateDefaultSubobject<UFiniteStateMachine>("Finite State Machine");

	// Create states
	m_GrazingState = CreateDefaultSubobject<UGrazingState>("Grazing State");
	m_FlockingState = CreateDefaultSubobject<UFlockingState>("Flocking State");

	// Create conditions
	m_TestCondition = CreateDefaultSubobject<UTestCondition>("Test Condition");
}

void APreyController::BeginPlay()
{
	Super::BeginPlay();

	// Set Behavior Tree classes
	m_GrazingState->InitializeState(this, GrazingBehaviorTree);

	// Create transitions
	FiniteStateMachine->SetStartState(m_GrazingState);
	FiniteStateMachine->AddTransition(m_GrazingState, m_FlockingState, m_TestCondition);
}
