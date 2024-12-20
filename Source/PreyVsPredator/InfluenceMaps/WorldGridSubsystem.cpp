#include "WorldGridSubsystem.h"

#include "Grid.h"


void UWorldGridSubsystem::SetupGrid(TSubclassOf<UWorldGridCell> WorldGridCellClass)
{
	// Create grid object
	m_WorldGrid = NewObject<UGrid>(GetWorld(), UGrid::StaticClass());

	// Set cell type to world grid cell
	m_WorldGrid->SetCellClass(WorldGridCellClass);

	// Fill grid with world grid cells
	m_WorldGrid->Initialize(StartPosition, Rows, Columns, CellSize);
}

float UWorldGridSubsystem::AcceptanceRadius() const
{
	return CellSize / AcceptanceDivisionFactor;
}

FVector UWorldGridSubsystem::NextCellPosition(const FVector& CurrentPosition, EWorldCellType Type) const
{
	const UGridCell* NextGridCell{m_WorldGrid->NextGridCell(CurrentPosition, Type)};
	if (NextGridCell == nullptr)
	{
		NextGridCell = m_WorldGrid->GridCellAtIndex(0);
	}

	return NextGridCell->CenterPosition();
}

bool UWorldGridSubsystem::AttemptConsumption(const FVector& CurrentPosition, EWorldCellType Type) const
{
	// Get cell we are currently in
	UWorldGridCell* CurrentWorldCell{Cast<UWorldGridCell>(m_WorldGrid->CurrentGridCell(CurrentPosition))};
	if (CurrentWorldCell != nullptr)
	{
		// Check if cell is type we want
		if (CurrentWorldCell->WorldType() == Type)
		{
			// Try to consume
			return CurrentWorldCell->Consume();
		}
	}

	return false;
}