#include "PreyVsPredatorGameModeBase.h"

#include "PreyVsPredator/InfluenceMaps/WorldGridSubsystem.h"


void APreyVsPredatorGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	checkf(WorldGridCellClass != nullptr, TEXT("World Grid Cell Class not assigned"));
	GetWorld()->GetSubsystem<UWorldGridSubsystem>()->SetupGrid(WorldGridCellClass);
}

void APreyVsPredatorGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
