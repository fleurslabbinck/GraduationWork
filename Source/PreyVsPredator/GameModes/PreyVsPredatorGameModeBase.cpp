#include "PreyVsPredatorGameModeBase.h"

#include "PreyVsPredator/InfluenceMaps/Grid.h"
#include "PreyVsPredator/InfluenceMaps/WorldGridSubsystem.h"


void APreyVsPredatorGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//UGrid* m_WorldGrid = NewObject<UGrid>(GetWorld(), UGrid::StaticClass());
	////m_WorldGrid->SetCellClass(GridCellClass);
	//m_WorldGrid->Initialize({}, 10, 10, 50.f);

	GetWorld()->GetSubsystem<UWorldGridSubsystem>()->SetupGrid();
}
