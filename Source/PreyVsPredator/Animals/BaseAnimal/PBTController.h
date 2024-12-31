#pragma once

#include "CoreMinimal.h"
#include "BaseController.h"
#include "PBTController.generated.h"

class UBehaviorTreeComponent;

UCLASS()
class PREYVSPREDATOR_API APBTController : public ABaseController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Behavior Tree")
	UBehaviorTree* BehaviorTree;

public:
	APBTController() = default;

protected:
	virtual void BeginPlay() override;
};
