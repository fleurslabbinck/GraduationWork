#include "FlockSubsystem.h"

#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"
#include "BaseFlock.h"

void UFlockSubsystem::UpdateFlocks()
{
	// Array to store flocks that need to be removed
	TArray<ABaseFlock*> FlocksToRemove;
	
	for (ABaseFlock* Flock : m_Flocks)
	{
		// Remove flocks that do not contain more than 1 entity
		if (Flock && Flock->TotalEntities() <= 1)
		{
			FlocksToRemove.Add(Flock);
		}
	}

	// Remove flocks
	for (ABaseFlock* FlockToRemove : FlocksToRemove)
	{
		m_Flocks.Remove(FlockToRemove);
		FlockToRemove->Destroy();
	}

	FlocksToRemove.Empty();
}

ABaseFlock* UFlockSubsystem::CreateFlock()
{
	ABaseFlock* NewFlock{GetWorld()->SpawnActor<ABaseFlock>()};
	if (NewFlock != nullptr)
	{
		m_Flocks.Add(NewFlock);
	}
	
	return NewFlock;
}

void UFlockSubsystem::MergeFlocks(ABaseFlock* Flock1, ABaseFlock* Flock2)
{
	if (Flock1 == nullptr || Flock2 == nullptr || Flock1 == Flock2) return;

	// Move entities from flock2 to flock1
	for (ABaseEntity* Entity : Flock2->Entities())
	{
		Flock1->AddEntity(Entity);
		Entity->SetFlock(Flock1);
	}

	// remove and destroy flock2
	m_Flocks.Remove(Flock2);
	Flock2->Destroy();
}
