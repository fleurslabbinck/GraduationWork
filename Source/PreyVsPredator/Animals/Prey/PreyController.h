// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PreyController.generated.h"

class UTestCondition;
class UFlockingState;
class UGrazingState;
class UFiniteStateMachine;

UCLASS()
class PREYVSPREDATOR_API APreyController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Instanced, Category="Components")
	UFiniteStateMachine* FiniteStateMachine;
public:
	APreyController();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UGrazingState* m_GrazingState;

	UPROPERTY()
	UFlockingState* m_FlockingState;

	UPROPERTY()
	UTestCondition* m_TestCondition;
};
