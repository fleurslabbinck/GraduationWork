﻿#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StateBase.generated.h"

class APreyController;
class UBlackboardComponent;

UCLASS()
class PREYVSPREDATOR_API UStateBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void OnEnter(APreyController* AIOwner, UBlackboardComponent* BlackboardComponent) {}
	virtual void Update(APreyController* AIOwner, UBlackboardComponent* BlackboardComponent, float DeltaTime) {}
	virtual void OnExit(APreyController* AIOwner, UBlackboardComponent* BlackboardComponent) {}
};
