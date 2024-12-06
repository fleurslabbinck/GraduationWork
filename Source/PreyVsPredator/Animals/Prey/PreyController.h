﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PreyVsPredator/Animals/Interfaces/AnimalControllerInterface.h"
#include "PreyController.generated.h"

class UBehaviorTree;
class UTestCondition;
class UFlockingState;
class UGrazingState;
class UFiniteStateMachine;

UCLASS()
class PREYVSPREDATOR_API APreyController : public AAIController, public IAnimalControllerInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Instanced, Category="Finite State Machine")
	UFiniteStateMachine* FiniteStateMachine;

	UPROPERTY(EditAnywhere, Category="Behavior Trees")
	UBehaviorTree* GrazingBehaviorTree;
	
public:
	APreyController();

	virtual void SetTimer(const FTimerDelegate& Delegate, float InRate) override;
	virtual void ResetTimer() override;

protected:
	virtual void BeginPlay() override;

private:
	FTimerHandle m_Timer{};
	
	UPROPERTY()
	UGrazingState* m_GrazingState;

	UPROPERTY()
	UFlockingState* m_FlockingState;

	UPROPERTY()
	UTestCondition* m_TestCondition;
};
