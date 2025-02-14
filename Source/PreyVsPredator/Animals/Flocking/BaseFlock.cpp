﻿#include "BaseFlock.h"

#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"

void ABaseFlock::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("Flock created"));
}

uint32 ABaseFlock::TotalEntities() const
{
	return m_Entities.Num();
}

TArray<ABaseEntity*> ABaseFlock::Entities()
{
	return m_Entities;
}

void ABaseFlock::AddEntity(ABaseEntity* NewEntity)
{
	if (!m_Entities.Contains(NewEntity))
	{
		m_Entities.Add(NewEntity);
		NewEntity->SetFlock(this);
	}
}

void ABaseFlock::RemoveEntity(ABaseEntity* EntityToRemove)
{
	m_Entities.Remove(EntityToRemove);
	EntityToRemove->SetFlock(nullptr);

	if (m_Entities.Num() <= 1)
	{
		OnFlockEmpty.Broadcast();
	}
}

bool ABaseFlock::Hungry() const
{
	return bHungry;
}

bool ABaseFlock::Thirsty() const
{
	return bThirsty;
}

void ABaseFlock::SetHungry()
{
	bHungry = true;
}

void ABaseFlock::SetThirsty()
{
	bThirsty = true;
}

void ABaseFlock::ResetNeeds()
{
	bHungry = false;
	bThirsty = false;
}

FVector ABaseFlock::FlockLocation() const
{
	FVector LocationSum = FVector::ZeroVector;

	if (!m_Entities.IsEmpty())
	{
		// Average position of flock
		for (const ABaseEntity* Entity : m_Entities)
		{
			LocationSum += Entity->GetActorLocation();
		}

		LocationSum /= m_Entities.Num();
	}

	return LocationSum;
}
