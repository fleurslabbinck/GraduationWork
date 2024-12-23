﻿#include "BaseFlock.h"

#include "BaseEntity.h"


void ABaseFlock::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Flock created"));
}

void ABaseFlock::BeginDestroy()
{
	Super::BeginDestroy();

	// Reset current flock to nullptr
	for (ABaseEntity* Entity : m_Entities)
	{
		Entity->SetFlock(nullptr);
	}

	m_Entities.Empty();
	
	UE_LOG(LogTemp, Warning, TEXT("Flock destroyed"));
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
}