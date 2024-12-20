﻿#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "PreyVsPredator/InfluenceMaps/GridData.h"
#include "BTT_GoToClosestType.generated.h"


UCLASS()
class PREYVSPREDATOR_API UBTT_GoToClosestType : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Params")
	EWorldCellType TargetType{EWorldCellType::Grass};

public:
	UBTT_GoToClosestType();

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	bool MoveToClosestTarget(const UBehaviorTreeComponent& OwnerComp) const;
};