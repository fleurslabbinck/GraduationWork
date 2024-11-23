#include "WorldGridSubsystem.h"

#include "Grid.h"


void UWorldGridSubsystem::SetupGrid()
{
	m_WorldGrid = NewObject<UGrid>(GetWorld(), UGrid::StaticClass());
	m_WorldGrid->SetCellClass(GridCellClass);
	m_WorldGrid->Initialize(StartPosition, Rows, Columns, CellSize);
}
