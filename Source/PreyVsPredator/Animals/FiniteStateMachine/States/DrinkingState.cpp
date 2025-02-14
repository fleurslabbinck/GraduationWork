﻿#include "DrinkingState.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PreyVsPredator/InfluenceMaps/WorldGridSubsystem.h"

class UWorldGridSubsystem;

UDrinkingState::UDrinkingState()
{
	m_MaxSpeed = m_MaxDrinkingSpeed;
}

void UDrinkingState::OnEnter(UBlackboardComponent* BlackboardComponent)
{
	Super::OnEnter(BlackboardComponent);

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("Drinking State"));
}

void UDrinkingState::OnExit(UBlackboardComponent* BlackboardComponent)
{
	Super::OnExit(BlackboardComponent);

	// Make sure entity is unsubscribed from cell when changing state
	AActor* Entity{m_AIController->GetPawn()};
	UWorldGridCell* CurrentCell {GetWorld()->GetSubsystem<UWorldGridSubsystem>()->CellAtPosition(BlackboardComponent->GetValueAsVector("ConsumeLocation"))};
	if (CurrentCell != nullptr)
	{
		CurrentCell->Unsubscribe(Entity);
	}
}
