#include "PreyVsPredatorGameModeBase.h"

#include "PreyVsPredator/Animals/BaseAnimal/BaseController.h"
#include "PreyVsPredator/Animals/BaseAnimal/BaseEntity.h"
#include "PreyVsPredator/Animals/Subsystems/WorldEventsSubsystem.h"
#include "PreyVsPredator/InfluenceMaps/WorldGridSubsystem.h"


void APreyVsPredatorGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	checkf(WorldGridCellClass != nullptr, TEXT("World Grid Cell Class not assigned"));
	checkf(PreyClass != nullptr, TEXT("Prey Class not assigned"));
	checkf(PreyControllerClass != nullptr, TEXT("Prey Controller Class not assigned"));

	// Initiate grid
	GetWorld()->GetSubsystem<UWorldGridSubsystem>()->SetupGrid(WorldGridCellClass);

	// Spawn entities
	for (uint32 Index{}; Index < MaxAmountPrey; ++Index)
	{
		SpawnEntity();
	}

	// Subscribe to event to always spawn entity when one entity dies
	GetWorld()->GetSubsystem<UWorldEventsSubsystem>()->OnEntityDeath.AddDynamic(this, &APreyVsPredatorGameModeBase::SpawnEntity);
}

void APreyVsPredatorGameModeBase::SpawnEntity()
{
	UWorld* World{GetWorld()};
	const FVector RandomPosition{World->GetSubsystem<UWorldGridSubsystem>()->RandomPositionInGrid()};

	// Always spawn
	FActorSpawnParameters SpawnParameters{};
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// Spawn entity
	ABaseEntity* Prey{Cast<ABaseEntity>(World->SpawnActor(PreyClass, &RandomPosition, {}, SpawnParameters))};
	ABaseController* PreyController{Cast<ABaseController>(World->SpawnActor(PreyControllerClass))};

	checkf(Prey != nullptr, TEXT("Prey did not spawn"));
	checkf(PreyController != nullptr, TEXT("Prey Controller did not spawn"));

	// Posses prey
	PreyController->Possess(Prey);
}
