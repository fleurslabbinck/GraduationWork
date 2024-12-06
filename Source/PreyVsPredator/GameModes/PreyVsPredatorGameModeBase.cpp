#include "PreyVsPredatorGameModeBase.h"

#include "PreyVsPredator/InfluenceMaps/Grid.h"
#include "PreyVsPredator/InfluenceMaps/WorldGridSubsystem.h"


void APreyVsPredatorGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetSubsystem<UWorldGridSubsystem>()->SetupGrid();
}

void APreyVsPredatorGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
