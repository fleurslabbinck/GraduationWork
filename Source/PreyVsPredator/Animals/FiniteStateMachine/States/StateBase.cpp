#include "StateBase.h"

#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseController.h"

void UStateBase::InitializeState(AAIController* AIController, UBehaviorTree* BehaviorTree)
{
	m_AIController = AIController;
	m_BehaviorTree = BehaviorTree;

	const ACharacter* ControlledCharacter{Cast<ACharacter>(m_AIController->GetPawn())};
	if (ControlledCharacter == nullptr) return;

	m_CharacterMovement = ControlledCharacter->GetCharacterMovement();
}

void UStateBase::OnEnter(UBlackboardComponent* BlackboardComponent)
{
	UpdateMaxSpeed();
	m_AIController->RunBehaviorTree(m_BehaviorTree);
}

void UStateBase::Update(UBlackboardComponent* BlackboardComponent, float DeltaTime)
{
	
}

void UStateBase::OnExit(UBlackboardComponent* BlackboardComponent)
{
	// Clear timer
	if (ABaseController* BaseController{Cast<ABaseController>(m_AIController)}; BaseController != nullptr)
	{
		BaseController->ResetTimer();
	}
}

void UStateBase::UpdateMaxSpeed()
{
	if (m_CharacterMovement == nullptr) return;
	m_CharacterMovement->MaxWalkSpeed = m_MaxSpeed;
}
