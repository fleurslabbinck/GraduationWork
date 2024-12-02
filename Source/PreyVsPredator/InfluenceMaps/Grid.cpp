#include "Grid.h"

#include "GridCell.h"

UGrid::UGrid()
{
	m_GridDirections.Add(FIntPoint(-1, 0));
	m_GridDirections.Add(FIntPoint(1, 0));
	m_GridDirections.Add(FIntPoint(0, -1));
	m_GridDirections.Add(FIntPoint(0, 1));
}

void UGrid::SetCellClass(const TSubclassOf<UGridCell> CellClass)
{
	m_GridCellClass = CellClass;
}

void UGrid::Initialize(const FVector& GridPosition, uint8 GridRows, uint8 GridColumns, float CellSize)
{
	m_Rows = GridRows;
	m_Columns = GridColumns;
	m_CellSize = CellSize;

	m_GridCells.Empty();

	// Starting bottom left
	FVector Pos{};
	UGridCell* Cell{};

	for (uint16 Row{}; Row < m_Rows; ++Row)
	{
		for (uint16 Column{}; Column < m_Columns; ++Column)
		{
			// Set position
			Pos.X = GridPosition.X + Row * CellSize;
			Pos.Y = GridPosition.Y + Column * CellSize;
			Pos.Z = GridPosition.Z;

			// Make cell
			Cell = NewObject<UGridCell>(GetWorld(), m_GridCellClass);
			Cell->Initialize(Pos, CellSize);
			Cell->DrawDebugCell(m_GridCells.Num());
			
			// Add to array
			m_GridCells.Add(Cell);
		}
	}
}

UGridCell* UGrid::NextGridCell(const FVector& CurrentPosition) const
{
	// Get the closest cell based on position (2D)
	const FVector2D CurrentPosition2D{CurrentPosition.X, CurrentPosition.Y};
	const uint32 ClosestCellIndex{ClosestCell(CurrentPosition2D)};

	// return gridcell if valid index
	return ClosestCellIndex != INDEX_NONE ? m_GridCells[ClosestCellIndex] : nullptr;
}

uint32 UGrid::CalculateIndex(uint32 Row, uint32 Column) const
{
	return Row * m_Columns + Column;
}

uint32 UGrid::RowFromIndex(uint32 Index) const
{
	return Index / m_Columns;
}

uint32 UGrid::ColumnFromIndex(uint32 Index) const
{
	return Index % m_Columns;
}

FVector UGrid::PositionFromIndex(uint32 Index) const
{
	if (Index >= static_cast<uint32>(m_GridCells.Num())) return FVector::ZeroVector;
	return m_GridCells[Index]->GridCell().Position;
}

uint32 UGrid::IndexFromPosition(const FVector2D& Position) const
{
	const uint32 Row{static_cast<uint32>(Position.X / m_CellSize)};
	const uint32 Column{static_cast<uint32>(Position.Y / m_CellSize)};
	const uint32 Index{Row * m_Columns + Column};
	
	return Index < static_cast<uint32>(m_GridCells.Num()) ? Index : INDEX_NONE;
}

uint32 UGrid::ClosestCell(const FVector2D& Position) const
{
	const uint32 StartIndex{IndexFromPosition(Position)};
	if (StartIndex == INDEX_NONE || StartIndex >= static_cast<uint32>(m_GridCells.Num())) return INDEX_NONE;

	// Setup Breadth-First-Search algorithm
	uint32 CurrentIndex;
	TQueue<uint32> Queue;
	TSet<uint32> Visited;

	Queue.Enqueue(StartIndex);
	Visited.Add(StartIndex);
	
	while (!Queue.IsEmpty())
	{
		Queue.Dequeue(CurrentIndex);

		// Check if cell is available
		if (m_GridCells[CurrentIndex]->Available())
		{
			return CurrentIndex;
		}

		// Add neighbors to queue
		TArray Neighbors{ValidNeighbors(CurrentIndex)};
		for (const uint32 Index : Neighbors)
		{
			if (!Visited.Contains(Index))
			{
				Queue.Enqueue(Index);
				Visited.Add(Index);
			}
		}
	}

	return INDEX_NONE;
}

TArray<uint32> UGrid::ValidNeighbors(uint32 Index) const
{
	TArray<uint32> Neighbors;
	Neighbors.Reserve(m_GridDirections.Num());

	for (const FIntPoint& Direction : m_GridDirections)
	{
		int32 Row{static_cast<int32>(RowFromIndex(Index) + Direction.X)};
		int32 Col{static_cast<int32>(ColumnFromIndex(Index) + Direction.Y)};

		// Check if valid
		if (Row >= 0 && Row < static_cast<int32>(m_Rows) &&
			Col >= 0 && Col <  static_cast<int32>(m_Columns))
		{
			Neighbors.Add(CalculateIndex(Row, Col));
		}
	}

	return Neighbors;
}
