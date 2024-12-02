#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_EatGrass.generated.h"


UCLASS()
class PREYVSPREDATOR_API UBTT_EatGrass : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Task")
	float EatTime{1.f};

public:
	UBTT_EatGrass();

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	FTimerHandle m_EatTimer{};
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UFUNCTION()
	void EatGrass(UBehaviorTreeComponent* OwnerComp);
};
