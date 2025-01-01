#include "BTD_IsDead.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTD_IsDead::UBTD_IsDead()
{
	DeadKey.AddBoolFilter(this, "Dead");
}

bool UBTD_IsDead::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return OwnerComp.GetBlackboardComponent()->GetValueAsBool(DeadKey.SelectedKeyName);
}
