#include "HFSMBTHController.h"

#include "PreyVsPredator/Animals/FiniteStateMachine/FiniteStateMachine.h"
#include "PreyVsPredator/Animals/FiniteStateMachine/Conditions/DeadCondition.h"
#include "PreyVsPredator/Animals/FiniteStateMachine/Conditions/FullWaterCondition.h"
#include "PreyVsPredator/Animals/FiniteStateMachine/Conditions/StartFlockingCondition.h"
#include "PreyVsPredator/Animals/FiniteStateMachine/Conditions/StopFlockingCondition.h"
#include "PreyVsPredator/Animals/FiniteStateMachine/Conditions/ThirstyCondition.h"
#include "PreyVsPredator/Animals/FiniteStateMachine/States/FlockingState.h"
#include "PreyVsPredator/Animals/FiniteStateMachine/States/GrazingState.h"
#include "PreyVsPredator/Animals/FiniteStateMachine/States/DrinkingState.h"
#include "PreyVsPredator/Animals/FiniteStateMachine/States/DyingState.h"


AHFSMBTHController::AHFSMBTHController()
{
	PrimaryActorTick.bCanEverTick = false;

	FiniteStateMachine = CreateDefaultSubobject<UFiniteStateMachine>("Finite State Machine");
}

void AHFSMBTHController::BeginPlay()
{
	Super::BeginPlay();

	// Create states
	m_GrazingState = NewObject<UGrazingState>(GetWorld());
	m_DrinkingState = NewObject<UDrinkingState>(GetWorld());
	m_FlockingState = NewObject<UFlockingState>(GetWorld());
	m_DyingState = NewObject<UDyingState>(GetWorld());

	// Create conditions
	m_ThirstyCondition = NewObject<UThirstyCondition>();
	m_FullWaterCondition = NewObject<UFullWaterCondition>();
	m_StartFlockingCondition = NewObject<UStartFlockingCondition>();
	m_StopFlockingCondition = NewObject<UStopFlockingCondition>();
	M_DeadCondition = NewObject<UDeadCondition>();

	checkf(GrazingBehaviorTree != nullptr, TEXT("Grazing Behavior Tree not assigned"));
	checkf(DrinkingBehaviorTree != nullptr, TEXT("Drinking Behavior Tree not assigned"));
	checkf(FlockingBehaviorTree != nullptr, TEXT("Flocking Behavior Tree not assigned"));
	checkf(DyingBehaviorTree != nullptr, TEXT("Dying Behavior Tree not assigned"));
}

void AHFSMBTHController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Set Behavior Tree classes
	m_GrazingState->InitializeState(this, GrazingBehaviorTree);
	m_DrinkingState->InitializeState(this, DrinkingBehaviorTree);
	m_FlockingState->InitializeState(this, FlockingBehaviorTree);
	m_DyingState->InitializeState(this, DyingBehaviorTree);

	// Create transitions
	FiniteStateMachine->SetStartState(m_GrazingState);
	FiniteStateMachine->AddTransition(m_GrazingState, m_DrinkingState, m_ThirstyCondition);
	FiniteStateMachine->AddTransition(m_DrinkingState, m_GrazingState, m_FullWaterCondition);
	FiniteStateMachine->AddTransition(m_GrazingState, m_FlockingState, m_StartFlockingCondition);
	FiniteStateMachine->AddTransition(m_FlockingState, m_GrazingState, m_StopFlockingCondition);
	FiniteStateMachine->AddTransition(m_GrazingState, m_DyingState, M_DeadCondition);
	FiniteStateMachine->AddTransition(m_DrinkingState, m_DyingState, M_DeadCondition);
	FiniteStateMachine->AddTransition(m_FlockingState, m_DyingState, M_DeadCondition);
}
