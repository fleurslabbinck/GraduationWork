#include "Grid.h"

#include "GridCell.h"

void UGrid::SetCellClass(const TSubclassOf<UGridCell> CellClass)
{
	m_GridCellClass = CellClass;
}

void UGrid::Initialize(const FVector2D& GridPosition, uint8 GridRows, uint8 GridColumns, float CellSize)
{
	m_Rows = GridRows;
	m_Columns = GridColumns;
	m_CellSize = CellSize;

	m_GridCells.Empty();

	// Starting bottom left
	FVector2D Pos{};
	UGridCell* Cell{};

	for (uint16 Row{}; Row < m_Rows; ++Row)
	{
		for (uint16 Column{}; Column < m_Columns; ++Column)
		{
			// Set position
			Pos.X = Row * CellSize;
			Pos.Y = Column * CellSize;

			// Make cell
			Cell = NewObject<UGridCell>(GetWorld(), m_GridCellClass);
			Cell->Initialize(Pos, CellSize);
			Cell->DrawDebugCell(m_GridCells.Num());
			
			// Add to array
			m_GridCells.Add(Cell);
		}
	}
}

FVector2D UGrid::PositionFromIndex(uint32 Index) const
{
	return m_GridCells[Index]->GridCell().Position;
}

uint32 UGrid::IndexFromPosition(FVector2D Position) const
{
	const uint32 Row{static_cast<uint32>(Position.X / m_CellSize)};
	const uint32 Column{static_cast<uint32>(Position.Y / m_CellSize)};

	return Row * m_Columns + Column;
}
