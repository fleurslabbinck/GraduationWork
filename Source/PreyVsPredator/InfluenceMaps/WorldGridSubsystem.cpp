#include "WorldGridSubsystem.h"

#include "Grid.h"


void UWorldGridSubsystem::SetPondSize(uint8 NewPondSize)
{
	PondSize = NewPondSize;
}

void UWorldGridSubsystem::SetupGrid(TSubclassOf<UWorldGridCell> WorldGridCellClass)
{
	// Create grid object
	m_WorldGrid = NewObject<UGrid>(GetWorld(), UGrid::StaticClass());

	// Set cell type to world grid cell
	m_WorldGrid->SetCellClass(WorldGridCellClass);

	// Fill grid with world grid cells
	m_WorldGrid->Initialize(StartPosition, Rows, Columns, CellSize);

	// Assign ponds
	// Top-left corner
	MakePond(0, 0);

	// Top-right corner
	MakePond(0, Columns - PondSize);

	// Bottom-left corner
	MakePond(Rows - PondSize, 0);

	// Bottom-right corner
	MakePond(Rows - PondSize, Columns - PondSize);

	// Middle (centered)
	const uint32 MidRow{Rows / 2 - PondSize / 2};
	const uint32 MidCol{Columns / 2 - PondSize / 2};
	MakePond(MidRow, MidCol);
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

void UWorldGridSubsystem::ChangeToWater(uint32 Index) const
{
	UWorldGridCell* Cell{Cast<UWorldGridCell>(m_WorldGrid->GridCellAtIndex(Index))};
	if (Cell != nullptr)
	{
		Cell->ChangeWorldType(EWorldCellType::Water);
	}
}

void UWorldGridSubsystem::MakePond(uint8 StartRow, uint8 StartCol) const
{
	for (uint8 Row{}; Row < PondSize; ++Row)
	{
		for (uint8 Col{}; Col < PondSize; ++Col)
		{
			const uint32 Index{(StartRow + Row) * Columns + (StartCol + Col)};
			ChangeToWater(Index);
		}
	}
}
