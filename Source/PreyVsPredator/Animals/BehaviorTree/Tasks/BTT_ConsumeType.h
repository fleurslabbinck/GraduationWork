#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "PreyVsPredator/Helpers/GridData.h"
#include "BTT_ConsumeType.generated.h"


UCLASS()
class PREYVSPREDATOR_API UBTT_ConsumeType : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Params")
	EWorldCellType TargetType{EWorldCellType::Grass};;

	UPROPERTY(EditAnywhere, Category="Params")
	float EatTime{1.f};

	UPROPERTY(EditAnywhere, Category="Blackboard Out")
	FBlackboardKeySelector ConsumeLocationKey;

public:
	UBTT_ConsumeType();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UFUNCTION()
	void ConsumeType(UBehaviorTreeComponent* OwnerComp);
};
