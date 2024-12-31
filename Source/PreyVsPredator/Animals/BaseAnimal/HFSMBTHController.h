#pragma once

#include "CoreMinimal.h"
#include "BaseController.h"
#include "HFSMBTHController.generated.h"

class UDeadCondition;
class UDyingState;
class UFullWaterCondition;
class UStopFlockingCondition;
class UThirstyCondition;
class UDrinkingState;
class UStartFlockingCondition;
class UBehaviorTree;
class UFlockingState;
class UGrazingState;
class UFiniteStateMachine;

UCLASS()
class PREYVSPREDATOR_API AHFSMBTHController : public ABaseController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Instanced, Category="Finite State Machine")
	UFiniteStateMachine* FiniteStateMachine;

	UPROPERTY(EditAnywhere, Category="Behavior Trees")
	UBehaviorTree* GrazingBehaviorTree;

	UPROPERTY(EditAnywhere, Category="Behavior Trees")
	UBehaviorTree* FlockingBehaviorTree;

	UPROPERTY(EditAnywhere, Category="Behavior Trees")
	UBehaviorTree* DrinkingBehaviorTree;

	UPROPERTY(EditAnywhere, Category="Behavior Trees")
	UBehaviorTree* DyingBehaviorTree;

public:
	AHFSMBTHController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	//==================================================================================================================
	// STATES
	//==================================================================================================================
	
	UPROPERTY()
	UGrazingState* m_GrazingState{nullptr};

	UPROPERTY()
	UDrinkingState* m_DrinkingState{nullptr};

	UPROPERTY()
	UFlockingState* m_FlockingState{nullptr};

	UPROPERTY()
	UDyingState* m_DyingState{nullptr};

	//==================================================================================================================
	// CONDITIONS
	//==================================================================================================================

	UPROPERTY()
	UThirstyCondition* m_ThirstyCondition{nullptr};

	UPROPERTY()
	UFullWaterCondition* m_FullWaterCondition{nullptr};

	UPROPERTY()
	UStartFlockingCondition* m_StartFlockingCondition{nullptr};

	UPROPERTY()
	UStopFlockingCondition* m_StopFlockingCondition{nullptr};

	UPROPERTY()
	UDeadCondition* M_DeadCondition{nullptr};
};
