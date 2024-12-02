#include "StateBase.h"

#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

void UStateBase::InitializeState(AAIController* AIController, UBehaviorTree* BehaviorTree)
{
	m_AIController = AIController;
	m_BehaviorTree = BehaviorTree;
}

void UStateBase::OnEnter(APreyController* AIOwner, UBlackboardComponent* BlackboardComponent)
{
	m_AIController->RunBehaviorTree(m_BehaviorTree);
}

void UStateBase::Update(APreyController* AIOwner, UBlackboardComponent* BlackboardComponent, float DeltaTime)
{
	
}

void UStateBase::OnExit(APreyController* AIOwner, UBlackboardComponent* BlackboardComponent)
{
	m_AIController->GetBrainComponent()->StopLogic(TEXT("Exiting State"));
}
