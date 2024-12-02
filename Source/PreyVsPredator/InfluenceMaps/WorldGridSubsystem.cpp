#include "WorldGridSubsystem.h"

#include "Grid.h"


void UWorldGridSubsystem::SetupGrid()
{
	// Create grid object
	m_WorldGrid = NewObject<UGrid>(GetWorld(), UGrid::StaticClass());

	// Set cell type to world grid cell
	m_WorldGrid->SetCellClass(GridCellClass);

	// Fill grid with world grid cells
	m_WorldGrid->Initialize(StartPosition, Rows, Columns, CellSize);
}

UGridCell* UWorldGridSubsystem::NextGrassPatch(const FVector& CurrentPosition) const
{
	return m_WorldGrid->NextGridCell(CurrentPosition);
}
