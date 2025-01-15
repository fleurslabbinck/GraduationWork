#include "WorldGridSubsystem.h"

#include "Grid.h"


void UWorldGridSubsystem::SetPondSize(uint8 NewPondSize)
{
	m_PondSize = NewPondSize;
}

void UWorldGridSubsystem::SetupGrid(TSubclassOf<UWorldGridCell> WorldGridCellClass, const FVector& StartPosition, uint32 Rows, uint32 Columns, float CellSize)
{
	m_CellSize = CellSize;
	m_Rows = Rows;
	m_Columns = Columns;
	
	// Create grid object
	m_WorldGrid = NewObject<UGrid>(GetWorld(), UGrid::StaticClass());

	// Set cell type to world grid cell
	m_WorldGrid->SetCellClass(WorldGridCellClass);

	// Fill grid with world grid cells
	m_WorldGrid->Initialize(StartPosition, Rows, Columns, CellSize);

	// Assign ponds
	constexpr uint32 PondRepetition{50};
	
	for (uint32 Row{}; Row < m_Rows; Row += PondRepetition)
		for (uint32 Col{}; Col < m_Columns; Col += PondRepetition)
	{
		{
			//const int Correction{PondRepetition - m_PondSize / 2};
			MakePond(Row, Col);
		}
	}
	
	// // Top-left corner
	// MakePond(0, 0);
	//
	// // Top-right corner
	// MakePond(0, Columns - m_PondSize);
	//
	// // Bottom-left corner
	// MakePond(Rows - m_PondSize, 0);
	//
	// // Bottom-right corner
	// MakePond(Rows - m_PondSize, Columns - m_PondSize);
	//
	// // Middle (centered)
	// const uint32 MidRow{Rows / 2 - m_PondSize / 2};
	// const uint32 MidCol{Columns / 2 - m_PondSize / 2};
	// MakePond(MidRow, MidCol);
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

float UWorldGridSubsystem::AcceptanceRadius() const
{
	return m_CellSize / m_AcceptanceDivisionFactor;
}

FVector UWorldGridSubsystem::RandomPositionInGrid() const
{
	int32 RandomIndex{FMath::RandRange(0, m_WorldGrid->TotalCells() - 1)};
	return m_WorldGrid->GridCellAtIndex(RandomIndex)->CenterPosition();
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

void UWorldGridSubsystem::MakePond(uint16 StartRow, uint16 StartCol) const
{
	for (uint8 Row{}; Row < m_PondSize; ++Row)
	{
		for (uint8 Col{}; Col < m_PondSize; ++Col)
		{
			const uint32 Index{(StartRow + Row) * m_Columns + (StartCol + Col)};
			ChangeToWater(Index);
		}
	}
}
