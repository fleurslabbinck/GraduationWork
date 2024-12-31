// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseController.generated.h"

UCLASS()
class PREYVSPREDATOR_API ABaseController : public AAIController
{
	GENERATED_BODY()
	
public:
	ABaseController() = default;

	void SetTimer(const FTimerDelegate& Delegate, float InRate);
	void ResetTimer();

private:
	FTimerHandle m_Timer{};
};
