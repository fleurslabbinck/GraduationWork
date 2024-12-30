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

	const uint32 TotalCells{m_WorldGrid->TotalCells()};

	// Assign water cells
	MakePond(0);
	MakePond(1);
	MakePond(Rows);
	MakePond(Rows + 1);
	
	MakePond(Rows - 1);
	MakePond(Rows - 2);
	MakePond(2 * Rows - 1);
	MakePond(2 * Rows - 2);
	
	MakePond(TotalCells / 2 + Rows / 2);
	MakePond(TotalCells / 2 - 1 + Rows / 2);
	MakePond(TotalCells / 2 - Rows / 2);
	MakePond(TotalCells / 2 - 1 - Rows / 2);
	
	MakePond(TotalCells - Rows);
	MakePond(TotalCells - Rows + 1);
	MakePond(TotalCells - 2 * Rows);
	MakePond(TotalCells - 2 * Rows + 1);
	
	MakePond(TotalCells - 1);
	MakePond(TotalCells - 2);
	MakePond(TotalCells - Rows - 1);
	MakePond(TotalCells - Rows - 2);
}

FVector UWorldGridSubsystem::RandomPositionInGrid() const
{
	int32 RandomIndex{FMath::RandRange(0, m_WorldGrid->TotalCells() - 1)};
	return m_WorldGrid->GridCellAtIndex(RandomIndex)->CenterPosition();
}

float UWorldGridSubsystem::AcceptanceRadius() const
{
	return CellSize / AcceptanceDivisionFactor;
}

FVector UWorldGridSubsystem::NextCellPosition(const FVector& CurrentPosition, EWorldCellType Type) const
{
	FVector NextPos{FVector::ZeroVector};
	if (const UGridCell* NextGridCell{m_WorldGrid->NextGridCell(CurrentPosition, Type)}; NextGridCell != nullptr)
	{
		NextPos = NextGridCell->CenterPosition();
	}

	return NextPos;
}

bool UWorldGridSubsystem::AttemptConsumption(const FVector& CurrentPosition, EWorldCellType Type) const
{
	// Get cell we are currently in
	UWorldGridCell* CurrentWorldCell{Cast<UWorldGridCell>(m_WorldGrid->GridCellAtPosition(CurrentPosition))};
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

UWorldGridCell* UWorldGridSubsystem::CellAtPosition(const FVector& Pos) const
{
	return Cast<UWorldGridCell>(m_WorldGrid->GridCellAtPosition(Pos));
}

void UWorldGridSubsystem::MakePond(uint32 Index) const
{
	UWorldGridCell* Cell{Cast<UWorldGridCell>(m_WorldGrid->GridCellAtIndex(Index))};
	if (Cell != nullptr)
	{
		Cell->ChangeWorldType(EWorldCellType::Water);
	}
}
