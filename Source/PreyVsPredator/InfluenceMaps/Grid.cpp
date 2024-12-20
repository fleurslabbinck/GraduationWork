#include "Grid.h"

#include "GridCell.h"
#include "WorldGridCell.h"

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
	UGridCell* Cell{};

	for (uint16 Row{}; Row < m_Rows; ++Row)
	{
		for (uint16 Column{}; Column < m_Columns; ++Column)
		{
			// Set position
			FVector Pos;
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

uint32 UGrid::TotalCells() const
{
	return m_GridCells.Num();
}

UGridCell* UGrid::CurrentGridCell(const FVector& CurrentPosition) const
{
	const FVector2D CurrentPosition2D{CurrentPosition.X, CurrentPosition.Y};
	const uint32 CurrentCellIndex{IndexFromPosition(CurrentPosition2D)};

	return CurrentCellIndex != INDEX_NONE ? m_GridCells[CurrentCellIndex] : nullptr;
}

UGridCell* UGrid::NextGridCell(const FVector& CurrentPosition, EWorldCellType Type) const
{
	// Get the closest cell based on position (2D)
	const FVector2D CurrentPosition2D{CurrentPosition.X, CurrentPosition.Y};
	const uint32 ClosestCellIndex{ClosestCell(CurrentPosition2D, Type)};

	// return gridcell if valid index
	return ClosestCellIndex != INDEX_NONE ? m_GridCells[ClosestCellIndex] : nullptr;
}

UGridCell* UGrid::GridCellAtIndex(uint32 Index) const
{
	if (Index < static_cast<uint32>(m_GridCells.Num()))
	{
		return m_GridCells[Index];
	}

	return nullptr;
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

FVector2D UGrid::PositionFromIndex(uint32 Index) const
{
	if (Index >= static_cast<uint32>(m_GridCells.Num())) return FVector2D::ZeroVector;
	return FVector2D{m_GridCells[Index]->CenterPosition()};
}

uint32 UGrid::IndexFromPosition(const FVector2D& Position) const
{
	const uint32 Row{static_cast<uint32>(Position.X / m_CellSize)};
	const uint32 Column{static_cast<uint32>(Position.Y / m_CellSize)};
	const uint32 Index{Row * m_Columns + Column};
	
	return Index < static_cast<uint32>(m_GridCells.Num()) ? Index : INDEX_NONE;
}

uint32 UGrid::ClosestCell(const FVector2D& Position, EWorldCellType Type) const
{
	const uint32 StartIndex{IndexFromPosition(Position)};
	if (StartIndex == INDEX_NONE || StartIndex >= static_cast<uint32>(m_GridCells.Num())) return INDEX_NONE;

	// Setup Breadth-First-Search algorithm
	uint32 CurrentIndex;
	TQueue<uint32> Queue;
	TSet<uint32> Visited;
	TArray<uint32> Neighbors;
	Neighbors.Reserve(m_GridDirections.Num());

	Queue.Enqueue(StartIndex);
	Visited.Add(StartIndex);
	
	while (!Queue.IsEmpty())
	{
		Queue.Dequeue(CurrentIndex);

		// Check if cell is available
		if (m_GridCells[CurrentIndex]->Available() && IsCellTypeValid(CurrentIndex, Type))
		{
			return CurrentIndex;
		}

		// Add neighbors to queue
		Neighbors.Empty();
		ValidNeighbors(Neighbors, Position, CurrentIndex, Type);
		
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

void UGrid::ValidNeighbors(TArray<uint32>& NeighborsArr, const FVector2D& Position, uint32 Index, EWorldCellType Type) const
{
	TArray<std::pair<uint32, float>> NeighborSqrDistances;
	NeighborSqrDistances.Reserve(m_GridDirections.Num());

	uint32 NeighborIndex{};

	for (const FIntPoint& Direction : m_GridDirections)
	{
		int32 Row{static_cast<int32>(RowFromIndex(Index) + Direction.X)};
		int32 Col{static_cast<int32>(ColumnFromIndex(Index) + Direction.Y)};

		// Check if within bounds
		if (Row >= 0 && Row < static_cast<int32>(m_Rows) &&
			Col >= 0 && Col <  static_cast<int32>(m_Columns))
		{
			NeighborIndex = CalculateIndex(Row, Col);

			// Avoid unnecessary calculations
			if (m_GridCells[NeighborIndex]->Available() && IsCellTypeValid(Index, Type))
			{
				const float DistanceSpr{static_cast<float>(FVector2D::DistSquared(Position, PositionFromIndex(NeighborIndex)))};
				NeighborSqrDistances.Add({NeighborIndex, DistanceSpr});
			}
			else
			{
				NeighborSqrDistances.Add({NeighborIndex, FLT_MAX});
			}
		}
	}

	NeighborSqrDistances.Sort([](const std::pair<uint32, float>& A, const std::pair<uint32, float>& B)
	{
		// Sort by distance
		return A.second < B.second;
	});

	for (const std::pair<uint32, float>&  Neighbor : NeighborSqrDistances)
	{
		NeighborsArr.Add(Neighbor.first);
	}
}

bool UGrid::IsCellTypeValid(uint32 Index, EWorldCellType Type) const
{
	switch (Type)
	{
	case EWorldCellType::None:
		return true;
		break;
	default:
		{
			UWorldGridCell* WorldGridCell{Cast<UWorldGridCell>(m_GridCells[Index])};
			if (WorldGridCell != nullptr)
			{
				return Type == WorldGridCell->WorldType();
			}
			break;
		}
	}

	return false;
}
