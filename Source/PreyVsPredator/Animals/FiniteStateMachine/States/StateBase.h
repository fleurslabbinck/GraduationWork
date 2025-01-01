#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StateBase.generated.h"

class UCharacterMovementComponent;
class UBehaviorTree;
class AAIController;
class UBlackboardComponent;

UCLASS()
class PREYVSPREDATOR_API UStateBase : public UObject
{
	GENERATED_BODY()

public:
	UStateBase() = default;
	
	void InitializeState(AAIController* AIController, UBehaviorTree* BehaviorTree);
	
	virtual void OnEnter(UBlackboardComponent* BlackboardComponent);
	virtual void Update(UBlackboardComponent* BlackboardComponent, float DeltaTime);
	virtual void OnExit(UBlackboardComponent* BlackboardComponent);

protected:
	float m_SpeedFactor{1.f};
	float m_MaxSpeed{600.f};
	
	UPROPERTY()
	AAIController* m_AIController{nullptr};
	
	UPROPERTY()
	UBehaviorTree* m_BehaviorTree{nullptr};

	UPROPERTY()
	UCharacterMovementComponent* m_CharacterMovement{nullptr};

	void UpdateMaxSpeed();
};
